//
// Created by fvfra on 07/05/2025.
//
#include <stdio.h>
#include <stdlib.h>

#include "./include/fast_piso.h"
#include "include/pq_con.h"
#include "include/utils.h"

int main() {
    // // init random state
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
    fast_piso_gen(&ks, 7680, state);
    // print keys
    fast_keys_print(&ks);

    // encrypt
    ciphertext_f ct;
    fast_ciphertext_init(&ct);
    fast_piso_enc(&ct, msg,  &ks.pk, state);

    fast_ciphertext_print(&ct);
    // decrypt
    fast_piso_dec(res, &ct, &ks);
    gmp_printf("res = %Zd\n", res);

    if (mpz_cmp(msg, res) == 0) {
        printf("Decryption successful!\n");
    } else {
        printf("Decryption failed!\n");
    }

    mpz_t d, g, p, rop;
    mpz_inits(d, g, p, rop, NULL);
    primes_q_p_by_size(ks.pk.q, p, 7680);
    primes_q_d_g_by_size(ks.pk.q, d, g, 7680);


    gmp_printf("g = %Zd\n", g);
    printf("g size in bits = %ld\n", mpz_sizeinbase(g, 2));

    param_t temp;
    param_inits(&temp, NULL);
    mpz_t two;
    mpz_init_set_ui(two, 2);
    mpz_set_ui(rop,1);
    while (1){
        mpz_add_ui(rop, rop, 1);
        mod_more_mpz(&temp, rop, two, d, ks.pk.q);
        const bool cond_1 = temp.inf;
        mod_more_mpz(&temp, rop, p, d, ks.pk.q);
        const bool cond_2 = temp.inf;
        if (!cond_1 && !cond_2) {
            break;
        }
    }
    mpz_clears(temp.value, two, NULL);

    gmp_printf("smallest generator for q is = %Zd\n", rop);
    printf("size in bits = %ld\n", mpz_sizeinbase(rop, 2));
}