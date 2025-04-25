//
// Created by fvfra on 25/04/2025.
//

#ifndef KEYS_H
#define KEYS_H

#include <gmp.h>
#include "params.h"

typedef struct {
    char *q;
    char *d;
    char *g;
    char *h;
} public_key;

typedef char* secret_key;

/**
 * A pair of public and secret keys for the ElGamal PISO scheme
 * where parameters are stored in hexadecimal format.
 */
typedef struct {
    public_key pk;
    secret_key sk;
} keys;

void public_key_from(public_key *pk, mpz_t q, mpz_t d, mpz_t g, param_t h);

void public_key_print(public_key pk);

void public_key_set(mpz_t q, mpz_t d, mpz_t g, mpz_t h, const public_key pk);

void secret_key_from(secret_key *sk, mpz_t n);
#endif //KEYS_H
