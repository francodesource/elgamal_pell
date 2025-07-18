//
// Created by fvfra on 16/04/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>

#include "include/utils.h"
#include "include/elgamal_piso.h"
#include "include/elgamal_proj.h"
#include "include/fast_cipher.h"
#include "include/fast_keys.h"
#include "include/fast_piso.h"

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

void benchmark_proj(int iterations, int sizeIndex, gmp_randstate_t state, mpz_t msg, mpz_t res) {
    float start;
    float t_gen;
    float t_enc;
    float t_dec;

    char filepath[100];
    sprintf(filepath, "%s/proj_benchmark_%d_%d_%d.csv",RESULT_PATH, sizes[0], sizes[sizeIndex - 1], iterations);
    FILE *fp = fopen(filepath, "w");
    fprintf(fp, CSV_HEADER);
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
}

void benchmark_piso(int iterations, int sizeIndex,  gmp_randstate_t state, mpz_t msg, mpz_t res) {
    float start, t_gen, t_enc, t_dec;
    char filepath[100];
    sprintf(filepath, "%s/piso_benchmark_%d_%d_%d.csv",RESULT_PATH, sizes[0], sizes[sizeIndex - 1], iterations);
    FILE *fp = fopen(filepath, "w");
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
}

void benchmark_piso_fast(int iterations, int sizeIndex,  gmp_randstate_t state, mpz_t msg, mpz_t res) {
    float start, t_gen, t_enc, t_dec;
    char filepath[100];
    sprintf(filepath, "%s/fast_piso_benchmark_%d_%d_%d.csv",RESULT_PATH, sizes[0], sizes[sizeIndex - 1], iterations);
    FILE *fp = fopen(filepath, "w");
    fprintf(fp, CSV_HEADER);

    keys_f ks;
    ciphertext_f ct;

    fast_ciphertext_init(&ct);
    fast_keys_init(&ks);


    // PISO BENCHMARKING
    printf("Running benchmark for PISO...\n");
    for (int i = 0; i < sizeIndex; ++i) {

        int size = sizes[i];
        printf("Running benchmark for size %d...\n", size);
        for (int j = 0; j < iterations; ++j) {

            start = timer();
            fast_piso_gen(&ks, size, state);
            t_gen = timer() - start;

            start = timer();
            fast_piso_enc(&ct, msg, &ks.pk, state);
            t_enc = timer() - start;

            start = timer();
            fast_piso_dec(res, &ct, &ks);
            t_dec = timer() - start;

            assert_eq(msg, res);

            fprintf(fp, "%f,%f,%f,%f,%d,PISO\n", t_gen, t_enc, t_dec, t_gen + t_enc + t_dec, size);
        }
    }
    fclose(fp);

}
int main(const int argc, char const *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <all | piso | proj > <iterations> <sizes 1-5>\n", argv[0]);
        return 1;
    }
    const char* algo = argv[1];
    int iterations = atoi(argv[2]);
    int sizeIndex  = atoi(argv[3]);

    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, arc4random());

    mpz_t msg, res;
    mpz_inits(msg, res, NULL);
    mpz_set_str(msg, "123456", 10);

    if (strcmp(algo, "all") == 0) {
        printf("Running benchmark for all algorithms...\n");
        benchmark_proj     (iterations, sizeIndex, state, msg, res);
        benchmark_piso     (iterations, sizeIndex, state, msg, res);
        benchmark_piso_fast(iterations, sizeIndex, state, msg, res);
    } else if (strcmp(algo, "piso") == 0) {
        benchmark_piso(iterations, sizeIndex, state, msg, res);
    } else if (strcmp(algo, "proj") == 0) {
        benchmark_proj(iterations, sizeIndex, state, msg, res);
    } else if (strcmp(algo, "fast") == 0) {
        benchmark_piso_fast(iterations, sizeIndex, state, msg, res);
    } else if (strcmp(algo, "piso-f") == 0) {
        benchmark_piso     (iterations, sizeIndex, state, msg, res);
        benchmark_piso_fast(iterations, sizeIndex, state, msg, res);
    } else {
        fprintf(stderr, "Invalid argument. Use 'all', 'piso' or 'proj'.\n");
        return 1;
    }

    return 0;

}
