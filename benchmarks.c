//
// Created by fvfra on 16/04/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "include/utils.h"
#include "include/elgamal_piso.h"
#include "include/elgamal_proj.h"

#define CSV_HEADER "gen,enc,dec,tot,size,algorithm\n"
/*
 * This file is used for benchmarking the algorithm
 * change the parameters below to test different sizes and iterations
 */

const int sizes[5] = { 512, 1024, 1536, 3840, 7680 };

void assert_eq(mpz_t a, mpz_t b) {
    if (mpz_cmp(a, b) != 0) {
        gmp_printf("Error: %Zd is not equal to %Zd\n", a, b);
        exit(EXIT_FAILURE);
    }
}

int main(const int argc, char const *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <iterations> <sizes 1-5>\n", argv[0]);
        return 1;
    }

    int iterations = atoi(argv[1]);
    int sizeIndex  = atoi(argv[2]);

    char filepath[100];
    sprintf(filepath, "%s/proj_benchmark_%d_%d_%d.csv",RESULT_PATH, sizes[0], sizes[sizeIndex - 1], iterations);

    FILE *fp = fopen(filepath, "w");
    // adding headers to csv
    fprintf(fp, CSV_HEADER);

    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, arc4random());

    mpz_t msg, res;
    mpz_inits(msg, res, NULL);
    mpz_set_str(msg, "123456", 10);

    float start, t_gen, t_enc, t_dec;


    // PROJ BENCHMARKING
    printf("Running benchmark for PROJ...\n");
    for (int i = 0; i < sizeIndex; ++i) {
        int size = sizes[i];
        printf("Running benchmark for size %d...\n", size);
        for (int j = 0; j < iterations; ++j) {
            start = timer();
            keys ks = proj_gen(size, state);
            t_gen = timer() - start;

            start = timer();
            ciphertext ct = proj_enc(msg, ks.pk, state);
            ct = proj_enc(msg, ks.pk, state); // Double encryption for benchmarking
            t_enc = timer() - start;

            start = timer();
            proj_dec(res, ct, ks.pk, ks.sk);
            proj_dec(res, ct, ks.pk, ks.sk); // Double decryption for benchmarking
            t_dec = timer() - start;

            assert_eq(msg, res);

            fprintf(fp, "%f,%f,%f,%f,%d,PROJ\n", t_gen, t_enc, t_dec, t_gen + t_enc + t_dec, size);
        }
    }
    fclose(fp);

    sprintf(filepath, "%s/piso_benchmark_%d_%d_%d.csv",RESULT_PATH, sizes[0], sizes[sizeIndex - 1], iterations);

    fp = fopen(filepath, "w");
    // adding headers to csv
    fprintf(fp, CSV_HEADER);

    // PISO BENCHMARKING
    printf("Running benchmark for PISO...\n");
    for (int i = 0; i < sizeIndex; ++i) {
        int size = sizes[i];
        printf("Running benchmark for size %d...\n", size);
        for (int j = 0; j < iterations; ++j) {

            start = timer();
            keys ks = piso_gen(size, state);
            t_gen = timer() - start;

            start = timer();
            ciphertext_d ct = piso_enc(msg, ks.pk, state);
            t_enc = timer() - start;

            start = timer();
            piso_dec(res, ct, ks.pk, ks.sk);
            t_dec = timer() - start;

            assert_eq(msg, res);

            fprintf(fp, "%f,%f,%f,%f,%d,PISO\n", t_gen, t_enc, t_dec, t_gen + t_enc + t_dec, size);
        }
    }
    fclose(fp);

    printf("Benchmarking completed. Results saved to %s and %s\n", filepath, filepath);
}
