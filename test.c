//
// Created by fvfra on 15/04/2025.
//

#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "results/location.c"
#include "src/params.c"
#include "src/keys.c"
#include "src/utils/utils.c"
#include "src/utils/pq_con.c"
#include "src/utils/tonelli_shanks.c"
#include "src/ciphertext.c"

#include "src/gen.c"
#include "src/enc.c"
#include "src/dec.c"

/*
 * This file is used for testing
 */

int test_gen_enc_dec_size_iter(int size) {
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, arc4random());
    mpz_t msg, res;
    mpz_inits(msg, res, NULL);

    const keys ks = gen(size, 1, state);
    // initializing message to a number with size bigger than q
    const int pad = size / 16;
    const int max_bits = 2 * (size - 1) - pad;
    mpz_rrandomb(msg, state, max_bits);
    const ciphertext ct = enc(msg, ks.pk, state, 1);
    dec(res, ct, ks.pk, ks.sk, 1);

    if (mpz_cmp(res, msg) != 0) {
        fprintf(stderr, "Error: message is not equal to message\n");
        return 1;
    }

    return 0;
}


int main(int argc, char *argv[]) {

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