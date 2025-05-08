//
// Created by fvfra on 07/05/2025.
//

#ifndef FAST_CIPHER_H
#define FAST_CIPHER_H

#include "params.h"

typedef struct {
    param_t c1;
    param_t c2;
    mpz_t d;
} ciphertext_f;

void fast_ciphertext_init(ciphertext_f *ct);
void fast_ciphertext_clear(ciphertext_f *ct);
void fast_ciphertext_print(ciphertext_f *ct);
#endif //FAST_CIPHER_H
