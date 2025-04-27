//
// Created by fvfra on 27/04/2025.
//

#include "../include/elgamal_proj.h"

#include <stdio.h>
#include <stdlib.h>

#include "../include/pq_con.h"
#include "../include/utils.h"

keys proj_gen(mp_bitcnt_t n, gmp_randstate_t state){

  mpz_t q, p, d, g, sk;
  param_t h;
  mpz_inits(q, p, d, g, sk, NULL);
  param_init(&h);

  if (!primes_q_p_by_size(q, p, n)) {
    rand_prime_q_p(q, p, state, n);
  }
  rand_non_square(d, state, q);
  rand_primitive_root(g, state, d, q, p);
  rand_range_ui(sk, state, 2, q);
  mod_more_mpz(&h, g, sk, d, q);

  keys ks;

  public_key_from(&ks.pk, q, d, g, h);
  secret_key_from(&ks.sk, sk);

  mpz_clears(q, p, d, g, sk, NULL);
  param_clears(&h, NULL);
  return ks;
}

ciphertext proj_enc(const mpz_t msg, const public_key pk, gmp_randstate_t state) {
  mpz_t q, d, g, r;
  param_t h, c1, c2;

  mpz_inits(q, d, g, r, NULL);
  param_inits(&h, &c1, &c2, NULL);

  public_key_set(q, d, g, &h, pk);

  // check message length
  if (mpz_cmp(msg, q) >= 0) {
    fprintf(stderr, "Error: message is too long\n");
    exit(EXIT_FAILURE);
  }
  // r <- random number in [2, q)
  rand_range_ui(r, state, 2, q);

  mod_more_mpz(&c1, g, r, d, q);
  mod_more(&c2, &h, r, d, q);
  param_op_mpz(&c2, &c2, msg, d, q);

  if (c2.inf) {
    printf("Infinite\n");
    gmp_printf("r: %Zx\n", r);
    gmp_printf("msg: %Zx\n", msg);
  }

  ciphertext ct;
  ciphertext_from(&ct, c1, c2);

  mpz_clears(q, d, g, h, r, NULL);
  param_clears(&c1, &c2, NULL);
  return ct;
}

void proj_dec(mpz_t rop, const ciphertext ct, const public_key pk, const secret_key _sk) {
  mpz_t q, d, sk;
  param_t c1, c2;
  mpz_inits(q, d, sk, NULL);
  param_inits(&c1, &c2, NULL);

  mpz_set_str(q, pk.q, 16);
  mpz_set_str(d, pk.d, 16);
  mpz_set_str(sk, _sk, 16);

  ciphertext_set(&c1, &c2, ct);
  mod_more(&c1, &c1, sk, d, q);

  param_invert(&c1, &c1, q);
  param_op(&c1, &c1, &c2, d, q);

  if (c1.inf) {
    fprintf(stderr, "Some error occurred during decryption\n");
    public_key_print(pk);
    ciphertext_print(ct);
    printf( "sk: %s", _sk);
    exit(EXIT_FAILURE);
  }

  mpz_set(rop, c1.value);
  mpz_clears(q, d, sk, NULL);
  param_clears(&c1, &c2, NULL);
}