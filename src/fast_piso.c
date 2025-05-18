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
    mpz_t q, d, g, r, p;
    mpz_inits(q, d, g, r, p, NULL);
    if (!primes_q_p_d_g_by_size(q, p, d, g, n)) {
        // if there are no primes of size n, we generate them
        rand_prime_q_p(q, p, state, n);
        smallest_non_square(d, q);
        rand_primitive_root(g, state, d, q, p);
    }

    rand_range_ui(ks->sk, state, 2, q);
    mod_more_mpz(&ks->pk.h, g, ks->sk, d, q);

    mpz_set(ks->pk.q, q);
    mpz_set(ks->pk.d, d);
    mpz_set(ks->pk.g, g);

    // freeing memory
    mpz_clears(q, d, g, p, r, NULL);
}

void fast_piso_enc(ciphertext_f * ct, const mpz_t msg, const public_key_f pk, gmp_randstate_t state) {

    mpz_t q, d, d1, g, x, y, m, r,  s, tmp;
    mpz_inits(q, d, d1, g, x, y, m, r, s, tmp, NULL);

    mpz_set(q, pk.q);
    mpz_set(d, pk.d);
    mpz_set(g, pk.g);


    // computing padding value
    const unsigned long q_bits = mpz_sizeinbase(pk.q, 2);
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
        mpz_mul(d1, x, x);
        mpz_sub_ui(d1, d1, 1);
        mpz_mod(d1, d1, q);
        if (mpz_jacobi(d1, q) == -1) {
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
    mpz_invert(y, y, pk.q);
    //  setting d
    mpz_powm_ui(tmp, y, 2, pk.q); // tmp <- y^2
    mpz_mul(d1, d1, tmp);
    mpz_mod(d1, d1, q); // d1 <- (x^2 - 1) / y^2

    // setting m
    mpz_add_ui(m, x, 1);
    mpz_mul(m, m, y);
    mpz_mod(m, m, q);

    // setting s
    mpz_invert(tmp, d, q);
    mpz_mul(tmp, tmp, d1); // tmp <- d^-1 * d1
    mpz_mod(tmp, tmp, q);

    sqrt_m(s, tmp, q);

    // setting random exponent r
    rand_range_ui(r, state, 2, q);

    // setting c1
    mpz_mul(tmp, g, s);
    mpz_mod(tmp, tmp, q);
    mod_more_mpz(&ct->c1, tmp, r, d1, q);

    if (pk.h.inf) {
        fprintf(stderr, "Error: h is infinite\n");
        exit(EXIT_FAILURE);
    }
    // setting c2
    mpz_mul(tmp, pk.h.value, s);
    mpz_mod(tmp, tmp, q);
    mod_more_mpz(&ct->c2, tmp, r, d1,q);
    param_op_mpz(&ct->c2, &ct->c2, m, d1, q);

    mpz_set(ct->d, d1);
    // freeing memory
    mpz_clears(q, d, d1, g, x, y, m, s, r, tmp, NULL);
}

void fast_piso_dec(mpz_t rop, const ciphertext_f *ct, const keys_f * ks) {

    mpz_t q, d1, x, y;
    mpz_inits(q, d1, x, y, NULL);

    mpz_set(q, ks->pk.q);
    mpz_set(d1, ct->d);
    param_t m;
    param_init(&m);
    unsigned long n = mpz_sizeinbase(q, 2);
    unsigned long pad = pd(n);

    mod_more(&m, &ct->c1, ks->sk, d1, q);
    param_invert(&m, &m, q);
    param_op(&m, &m, &ct->c2, d1, q); // (-c1^sk) * c2

    param_coord(x, y, &m, d1, q);
    mpz_tdiv_q_2exp(x, x, pad);
    mpz_mul_2exp(rop, x, n - 1);
    mpz_sub_ui(y, y, 1);
    mpz_add(rop, rop, y);
    mpz_clears(q, d1, x, y, NULL);
}