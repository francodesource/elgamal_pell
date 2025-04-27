//
// Created by fvfra on 27/04/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "../include/elgamal_proj.h"
#include "../include/utils.h"

/*
 * This file is used for testing
 */


int test_gen_enc_dec_size_iter(const int size) {
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, arc4random());
    mpz_t msg, res, q;
    mpz_inits(msg, res, q, NULL);

    const keys ks = proj_gen(size, state);
    mpz_set_str(q, ks.pk.q, 16);
    rand_range_ui(msg, state, 2, q);
    const ciphertext ct = proj_enc(msg, ks.pk, state);
    proj_dec(res, ct, ks.pk, ks.sk);

    if (mpz_cmp(res, msg) != 0) {
        gmp_fprintf(stderr, "Error: message %Zd is not equal to message %Zd\n", res, msg);
        return 1;
    }

    return 0;
}


int main(const int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <size> <iter>\n", argv[0]);
        return 1;
    }
    const int size = atoi(argv[1]);
    const int iter = atoi(argv[2]);

    for (int i = 0; i < iter; i++) {
        if (test_gen_enc_dec_size_iter(size) != 0) {
            fprintf(stderr, "Test failed for size %d and iter %d\n", size, iter);
            return 1;
        }
    }

    printf("Test passed %d iterations for size %d \n", iter, size);

    return 0;
}