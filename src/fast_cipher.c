//
// Created by fvfra on 07/05/2025.
//

#include "../include/fast_cipher.h"

#include <stdio.h>

void fast_ciphertext_init(ciphertext_f *ct) {
    mpz_init(ct->d);
    param_inits(&ct->c1, &ct->c2, NULL);
 }

void fast_ciphertext_clear(ciphertext_f *ct) {
    mpz_clear(ct->d);
    param_clears(&ct->c1, &ct->c2, NULL);
}

void fast_ciphertext_print(ciphertext_f *ct) {
    printf("ciphertext:\n");
    gmp_printf("c1: %s\n", param_get_str(ct->c1));
    gmp_printf("c2: %s\n", param_get_str(ct->c2));
    gmp_printf("d: %Zd\n", ct->d);
}