//
// Created by fvfra on 07/05/2025.
//

#include <stdio.h>

#include "../include/fast_keys.h"

void public_key_f_init(public_key_f *pk) {
    mpz_inits(pk->q, pk->d, pk->g, NULL);
    param_init(&pk->h);
}
void public_key_f_clear(public_key_f *pk){
    mpz_clears(pk->q, pk->d, pk->g, NULL);
    param_clear(&pk->h);
}

void fast_keys_init(keys_f *ks) {
    public_key_f_init(&ks->pk);
    mpz_init(ks->sk);
}
void fast_keys_clear(keys_f *ks) {
    public_key_f_clear(&ks->pk);
    mpz_clear(ks->sk);
}
void fast_keys_print(keys_f *ks) {
    printf("Public key\n");
    gmp_printf("q = %Zd\n", ks->pk.q);
    gmp_printf("d = %Zd\n", ks->pk.d);
    gmp_printf("g = %Zd\n", ks->pk.g);
    printf("h = %s\n", param_get_str(ks->pk.h));
}

void fast_keys_set(keys_f *ks, const keys_f *ks2) {

    mpz_set(ks->sk, ks2->sk);
}