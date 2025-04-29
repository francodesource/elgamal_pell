//
// Created by fvfra on 14/04/2025.
//
#include <stdio.h>
#include <stdlib.h>

#include "../include/keys.h"
#include "../include/elgamal_piso.h"
#include "../include/params.h"
#include "../include/utils.h"
#include "../include/ciphertext.h"
#include "../include/pq_con.h"

unsigned long padding(unsigned long size) {
    if (size < 512) return size / 8;
    return size / 16;
}

keys piso_gen(mp_bitcnt_t n, gmp_randstate_t state) {
    mpz_t g, q, p, d, sk;
    mpz_inits(g, q, p, d, sk, NULL);

    param_t h;
    param_init(&h);

    if (!primes_q_p_by_size(q, p, n)) {
        // if there are no primes of size n, we generate them
        rand_prime_q_p(q, p, state, n);
    }
    smallest_non_square(d, q);
    rand_primitive_root(g, state, d, q, p);

    // measuring time for exponentiation
    rand_range_ui(sk, state, 2, q);
    mod_more_mpz(&h, g, sk, d, q);


    // returning the key as hex strings
    keys res;
    public_key_from(&res.pk, q, d, g, h);
    secret_key_from(&res.sk, sk);

    // freeing memory
    mpz_clears(g, q, p, d, sk, NULL);
    param_clears(&h, NULL);

    return res;

}

ciphertext_d piso_enc(const mpz_t msg, const public_key pk, gmp_randstate_t state) {
    mpz_t q, d, d1, g, x, y, m, s, r, tmp;
    mpz_inits(q, d, d1, g, x, m, y, s, r, tmp, NULL);
    param_t h, c1, c2;
    param_inits(&h, &c1, &c2, NULL);;
    // q, d, g, h must not be modified inside the loop
    public_key_set(q, d, g, &h, pk); // converting from hexadecimal to mpz_t
    // computing padding value
    const unsigned long q_bits = mpz_sizeinbase(q, 2);
    const unsigned long pad = padding(q_bits);
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
    if (mpz_invert(y, y, q) == 0) { // y <- y^-1
        gmp_fprintf(stderr, "Error: y (%Zd) is not invertible\n",y);
        exit(EXIT_FAILURE);
    }
    //  setting d
    mpz_powm_ui(tmp, y, 2, q); // tmp <- y^2
    mpz_mul(d1, d1, tmp);
    mpz_mod(d1, d1, q); // d1 <- (x^2 - 1) / y^2

    // setting m
    mpz_add_ui(m, x, 1);
    mpz_mul(m, m, y);
    mpz_mod(m, m, q);
    // setting random exponent r
    rand_range_ui(r, state, 2, q);
    // setting s
    mpz_invert(tmp, d, q);
    mpz_mul(tmp, tmp, d1); // tmp <- d^-1 * d1
    mpz_mod(tmp, tmp, q);

    sqrt_m(s, tmp, q);

    // setting c1 & c2
    mpz_mul(tmp, g, s);
    mpz_mod(tmp, tmp, q);
    mod_more_mpz(&c1, tmp, r, d1, q);

    if (h.inf) {
        fprintf(stderr, "Error: h is infinite\n");
        exit(EXIT_FAILURE);
    }

    mpz_mul(tmp, h.value, s);
    mpz_mod(tmp, tmp, q);
    mod_more_mpz(&c2, tmp, r, d1, q);
    param_op_mpz(&c2, &c2, m, d1, q);

    const ciphertext_d ct = {
        .c1 = param_get_str(c1),
        .c2 = param_get_str(c2),
        .d  = mpz_get_str(NULL, 16, d1)
    };

    // freeing memory
    mpz_clears(q, d, d1, g, h, x, m, s, r, tmp, NULL);
    param_clears(&c1, &c2, NULL);
    return ct;
}

void piso_dec(mpz_t rop, const ciphertext_d ct, const public_key pk, const secret_key _sk) {
    mpz_t x, y, d1, q, sk;
    param_t c1, c2, m; // c1 and c2 must  not be modified inside the loop

    param_inits(&c1, &c2, &m, NULL);
    mpz_inits(x, y, d1, q, sk, NULL);

    ciphertext_d_set(&c1, &c2, d1, ct);
    mpz_set_str(sk, _sk, 16);
    mpz_set_str(q, pk.q, 16);
    unsigned long n = mpz_sizeinbase(q, 2);
    unsigned long pad = padding(n);

    mod_more(&m, &c1, sk, d1, q);
    param_invert(&m, &m, q);
    param_op(&m, &m, &c2, d1, q); // (-c1^sk) * c2

    param_coord(x, y, &m, d1, q);
    mpz_tdiv_q_2exp(x, x, pad);
    mpz_mul_2exp(rop, x, n - 1);
    mpz_sub_ui(y, y, 1);
    mpz_add(rop, rop, y);

    mpz_clears(x, y, d1, q, sk, NULL);
    param_clears(&c1, &c2, &m, NULL);
}
