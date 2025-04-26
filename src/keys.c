//
// Created by fvfra on 11/04/2025.
//

#include "../include/keys.h"

#include <stdio.h>

void public_key_from(public_key *pk, mpz_t q, mpz_t d, mpz_t g, param_t h){
    pk->q = mpz_get_str(NULL, 16, q);
    pk->d = mpz_get_str(NULL, 16, d);
    pk->g = mpz_get_str(NULL, 16, g);
    pk->h = param_get_str(h);
}

void public_key_print(public_key pk) {
    printf("Public Key:\nq: %s\nd: %s\ng: %s\nh: %s\n", pk.q, pk.d, pk.g, pk.h);
}

void public_key_set(mpz_t q, mpz_t d, mpz_t g, mpz_t h, const public_key pk) {
    mpz_set_str(q, pk.q, 16);
    mpz_set_str(d, pk.d, 16);
    mpz_set_str(g, pk.g, 16);
    mpz_set_str(h, pk.h, 16);
}

void secret_key_from(secret_key *sk, mpz_t n){
    *sk = mpz_get_str(NULL, 16, n);
}