//
// Created by fvfra on 07/05/2025.
//
#include <stdlib.h>
#include <stdio.h>

#include "../include/fast_piso.h"
#include "../include/pq_con.h"
#include "../include/utils.h"
static unsigned long pd(unsigned long size) {
    if (size < 512) return size / 8;
    return size / 16;
}

void fast_piso_gen(keys_f * ks, mp_bitcnt_t n, gmp_randstate_t state) {
    mpz_t r;
    mpz_init(r);
    if (!primes_q_d_g_by_size(ks->pk.q, ks->pk.d, ks->pk.g, n)) {
        mpz_t p;
        mpz_init(p);
        // if there are no primes of size n, we generate them
        rand_prime_q_p(ks->pk.q, p, state, n);
        smallest_non_square(ks->pk.d, ks->pk.q);
        rand_primitive_root(ks->pk.g, state, ks->pk.d, ks->pk.q, p);
        mpz_clear(p);
    }
    rand_range_ui(ks->sk, state, 2, ks->pk.q);
    mod_more_mpz(&ks->pk.h, ks->pk.g, ks->sk, ks->pk.d, ks->pk.q);
    // freeing memory
    mpz_clear(r);
}

void fast_piso_enc(ciphertext_f * ct, const mpz_t msg, const public_key_f * pk, gmp_randstate_t state) {
    mpz_t x, y, m, r,  s, tmp;
    mpz_inits(x, y, m, r, s, tmp, NULL);

    // computing padding value
    const unsigned long q_bits = mpz_sizeinbase(pk->q, 2);
    const unsigned long pad = pd(q_bits);

    // check if message has correct size
    if (mpz_sizeinbase(msg, 2) > 2 * (q_bits - 1) - pad) {
        perror("Error: message is too long\n");
        exit(EXIT_FAILURE);
    }

    // splitting message in two coordinates
    mpz_tdiv_q_2exp(x, msg, q_bits - 1);
    // padding the message
    mpz_mul_2exp(x, x, pad);

    // finding a suitable d
    bool found = false;
    for (unsigned long int j = 0; j < pad; j++) {
        mpz_mul(ct->d, x, x);
        mpz_sub_ui(ct->d, ct->d, 1);
        mpz_mod(ct->d, ct->d, pk->q);
        if (mpz_jacobi(ct->d, pk->q) == -1) {
            found = true;
            break;
        }
        mpz_add_ui(x, x, 1);
    }

    // exit the program if no suitable d is found
    if (!found) {
        perror("Error: non square d found\n");
        exit(EXIT_FAILURE);
    }
    // setting y <- msg % (n - 1) + 1
    mpz_tdiv_r_2exp(y, msg, q_bits - 1);
    mpz_add_ui(y, y, 1);

    // (???)
    // aggiungo uno a y cosí é sempre diverso da zero e posso invertirlo altrimenti
    // l'algoritmo crasha per messaggi del tipo 110000...000
    // bisogna sottrarre uno anche in fase di decryption

    // Handling case where y is not invertible
    mpz_invert(y, y, pk->q);
    //  setting d
    mpz_powm_ui(tmp, y, 2, pk->q); // tmp <- y^2
    mpz_mul(ct->d, ct->d, tmp);
    mpz_mod(ct->d, ct->d, pk->q); // d1 <- (x^2 - 1) / y^2

    // setting m
    mpz_add_ui(m, x, 1);
    mpz_mul(m, m, y);
    mpz_mod(m, m, pk->q);

    // setting s
    mpz_invert(tmp, pk->d, pk->q);
    mpz_mul(tmp, tmp, ct->d); // tmp <- d^-1 * d1
    mpz_mod(tmp, tmp, pk->q);

    sqrt_m(s, tmp, pk->q);

    rand_range_ui(r, state, 2, pk->q);

    // setting c1
    mpz_mul(tmp, pk->g, s);
    mpz_mod(tmp, tmp, pk->q);
    mod_more_mpz(&ct->c1, tmp, r, ct->d, pk->q);

    if (pk->h.inf) {
        fprintf(stderr, "Error: h is infinite\n");
        exit(EXIT_FAILURE);
    }
    // setting c2
    mpz_mul(tmp, pk->h.value, s);
    mpz_mod(tmp, tmp, pk->q);
    mod_more_mpz(&ct->c2, tmp, r, ct->d,pk->q);
    param_op_mpz(&ct->c2, &ct->c2, m, ct->d, pk->q);

    // freeing memory
    mpz_clears(x, y, m, s, r, tmp, NULL);
}

void fast_piso_dec(mpz_t rop, const ciphertext_f *ct, const keys_f * ks) {

    mpz_t x, y;
    mpz_inits(x, y, NULL);

    param_t m;
    param_init(&m);
    const unsigned long n = mpz_sizeinbase(ks->pk.q, 2);
    const unsigned long pad = pd(n);

    mod_more(&m, &ct->c1, ks->sk, ct->d, ks->pk.q);
    param_invert(&m, &m, ks->pk.q);
    param_op(&m, &m, &ct->c2, ct->d, ks->pk.q); // (-c1^sk) * c2

    param_coord(x, y, &m, ct->d, ks->pk.q);
    mpz_tdiv_q_2exp(x, x, pad);
    mpz_mul_2exp(rop, x, n - 1);
    mpz_sub_ui(y, y, 1);
    mpz_add(rop, rop, y);
    mpz_clears(x, y, NULL);
}