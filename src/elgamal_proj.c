//
// Created by fvfra on 27/04/2025.
//

#include "../include/elgamal_proj.h"
#include "../include/pq_con.h"
#include "../include/utils.h"

keys proj_gen(mp_bitcnt_t n, gmp_randstate_t state){

  mpz_t q, p, d, g, sk;
  param_t h;
  mpz_inits(q, p, d, g, sk NULL);
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
