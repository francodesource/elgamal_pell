//
// Created by fvfra on 07/05/2025.
//
#include <stdlib.h>

#include "./include/fast_piso.h"

int main() {
    // init random state
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, arc4random());

    mpz_t msg, res;
    mpz_inits(msg, res, NULL);
    mpz_set_ui(msg, 123456);
    // init keys
    keys_f ks;
    fast_keys_init(&ks);
    // generate keys
    fast_piso_gen(&ks, 1024, state);
    // print keys
    fast_keys_print(&ks);

    // encrypt
    ciphertext_f ct;
    fast_ciphertext_init(&ct);
    fast_piso_enc(&ct, msg,  ks.pk, state);

    fast_ciphertext_print(&ct);
    // decrypt
    fast_piso_dec(res, &ct, &ks);
    gmp_printf("res = %Zd\n", res);

    return 0;
}