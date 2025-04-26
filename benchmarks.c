//
// Created by fvfra on 16/04/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>

#include "./include/elgamal_piso.h"

/*
 * This file is used for benchmarking the algorithm
 * change the parameters below to test different sizes and iterations
 */

#define FITER 10
#define ITER  10
#define NSIZE  5 // 5 tests all known sizes
#define MSG   "123456"

const int sizes[] = { 512, 1024, 1536, 3840, 7680 };

typedef struct {
    float * t_par;
    float * t_mul;
    float * t_enc;
    float * t_dec;
} times;

void times_clear(times * t) {
    free(t->t_par);
    free(t->t_mul);
    free(t->t_enc);
    free(t->t_dec);
}

void clean_file(const char * filepath) {
    FILE *file = fopen(filepath, "w");
    fprintf(file, "%s", ""); // clear the file
    fclose(file);
}

void assert_eq(mpz_t a, mpz_t b) {
    if (mpz_cmp(a, b) != 0) {
        gmp_printf("Error: %Zd is not equal to %Zd\n", a, b);
        exit(EXIT_FAILURE);
    }
}

times read_formatted_file(const char * filepath, const int iter) {
    FILE *file = fopen(filepath, "r");

    char buffer[256];
    float * t_par = malloc(iter * sizeof(float));
    float * t_mul = malloc(iter * sizeof(float));
    float * t_enc = malloc(iter * sizeof(float));
    float * t_dec = malloc(iter * sizeof(float));

    for (int i = 0; i < iter; i++) {
        fgets(buffer, sizeof(buffer), file);
        fscanf(file, "time(par)\t%f\n", t_par +i);
        fscanf(file, "time(mul)\t%f\n", t_mul + i);
        fgets(buffer, sizeof(buffer), file);
        fscanf(file, "time(enc)\t%f\n", t_enc+i);
        fgets(buffer, sizeof(buffer), file);
        fscanf(file, "time(dec)\t%f\n", t_dec+i);
    }

    fclose(file);
    times res = {t_par, t_mul, t_enc, t_dec};
    return res;
}

float mean(float * vec, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += vec[i];
    }
    return sum / (float) size;
}

int main() {

    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, arc4random());
    char means_file[100];
    sprintf(means_file, "%s/means", RESULT_PATH);
    FILE * means = fopen(means_file, "w");
    fprintf(means, "%s", ""); // clear file from previous runs
    fclose(means);
    means = fopen(means_file, "a");
    for (int i = 0; i < NSIZE; i++) {
        char filepath[100];
        sprintf(filepath, "%s/elgamal_piso_%d_%d", RESULT_PATH, sizes[i], FITER);
        clean_file(filepath);
        printf("computing benchmarks for size %d, iterations %d\n", sizes[i], FITER);
        for (int j = 0; j < ITER; j++) {
            mpz_t msg, res;
            mpz_inits(msg, res, NULL);
            mpz_set_str(msg, MSG, 10);

            const keys ks = piso_gen(sizes[i], FITER, state);
            const ciphertext ct = piso_enc(msg, ks.pk, state, FITER);
            piso_dec(res, ct, ks.pk, ks.sk, FITER);

            // checking if encryption and decryption were successful
            assert_eq(res, msg);
        }
        times ts = read_formatted_file(filepath, ITER);
        float t_par_mean = mean(ts.t_par, ITER);
        float t_mul_mean = mean(ts.t_mul, ITER);
        float t_gen_mean = t_par_mean + t_mul_mean;
        float t_enc_mean = mean(ts.t_enc, ITER);
        float t_dec_mean = mean(ts.t_dec, ITER);

        fprintf(means, "*** Size %d ***", sizes[i]);
        fprintf(means, "time(par)\t%f\n", t_par_mean);
        fprintf(means, "time(mul)\t%f\n", t_mul_mean);
        fprintf(means, "time(gen)\t%f\n", t_gen_mean);
        fprintf(means, "time(enc)\t%f\n", t_enc_mean);
        fprintf(means, "time(dec)\t%f\n", t_dec_mean);
        fprintf(means, "time(total)\t%f\n", t_gen_mean + t_enc_mean + t_dec_mean);
        times_clear(&ts);
    }
}
