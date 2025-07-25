//
// Created by fvfra on 14/04/2025.
//

# include "../include/ciphertext.h"

#include <stdio.h>
#include <stdlib.h>

void ciphertext_from(ciphertext *ct, const param_t c1, const param_t c2){
    ct->c1 = param_get_str(c1);
    ct->c2 = param_get_str(c2);
}

void ciphertext_print(const ciphertext ct) {
    printf("ciphertext:\nc1: %s\nc2: %s\n", ct.c1, ct.c2);
}

void ciphertext_set(param_t * c1, param_t * c2, const ciphertext ct) {
    param_set_str(c1, ct.c1, 16);
    param_set_str(c2, ct.c2, 16);
}

void ciphertext_clear(ciphertext * ct) {
    free(ct->c1);
    free(ct->c2);
}

void ciphertext_d_from(ciphertext_d *ct, const param_t c1, const param_t c2, mpz_t d){
    ct->c1 = param_get_str(c1);
    ct->c2 = param_get_str(c2);
    ct->d = mpz_get_str(NULL, 16, d);
}

void ciphertext_d_print(ciphertext_d ct) {
    printf("ciphertext:\nc1: %s\nc2: %s\nd: %s\n", ct.c1, ct.c2, ct.d);
}

void ciphertext_d_set(param_t * c1, param_t * c2, mpz_t d, const ciphertext_d ct) {
    param_set_str(c1, ct.c1, 16);
    param_set_str(c2, ct.c2, 16);
    mpz_set_str(d, ct.d, 16);
}

void ciphertext_d_clear(ciphertext_d * ct) {
    free(ct->c1);
    free(ct->c2);
    free(ct->d);
}
