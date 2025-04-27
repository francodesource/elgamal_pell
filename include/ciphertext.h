//
// Created by fvfra on 25/04/2025.
//

#ifndef CIPHERTEXT_H
#define CIPHERTEXT_H

#include "./params.h"

typedef struct {
    char *c1;
    char *c2;
} ciphertext;

void ciphertext_from(ciphertext *ct, param_t c1, param_t c2);
void ciphertext_print(ciphertext ct);
void ciphertext_set(param_t * c1, param_t * c2, const ciphertext ct);

typedef struct {
    char * c1;
    char * c2;
    char * d;
} ciphertext_d;

void ciphertext_d_from(ciphertext_d *ct, param_t c1, param_t c2, mpz_t d);
void ciphertext_d_print(ciphertext_d ct);
void ciphertext_d_set(param_t * c1, param_t * c2, mpz_t d, const ciphertext_d ct);
#endif //CIPHERTEXT_H
