//
// Created by fvfra on 15/05/2025.
//

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/fast_piso.h"
#include "../include/params.h"
#include "../include/utils.h"

void mod_more_mpz_old(param_t * rop, const mpz_t m, const mpz_t e, const mpz_t d, const mpz_t q) {
    mpz_t N, D, Nt, Dt, temp;
    mpz_inits(N, D, Nt, Dt, temp, NULL);

    mpz_set_ui(N, 1);
    mpz_set_ui(D, 0);

    for (int i = mpz_sizeinbase(e, 2); i >= 0; --i) {
        const int bit = mpz_tstbit(e, i);

        // saving values of N and D
        mpz_set(Nt, N);
        mpz_set(Dt, D);

        // N' = N^2 + dD^2 in F_q
        mpz_pow_ui(D, Dt, 2);
        mpz_mul(D, D, d);
        mpz_pow_ui(N, Nt, 2);

        mpz_add(N, N, D);
        mpz_mod(N, N, q);

        // D' = 2ND in F_q
        mpz_mul(D, Dt, Nt);
        mpz_mul_ui(D, D, 2);
        mpz_mod(D, D, q);

        if (bit == 1) {
            // saving values of N and D
            mpz_set(Nt, N);
            mpz_set(Dt, D);

            //N' = Nm + dD in F_q
            mpz_mul(D, Dt, d);
            mpz_mul(N, Nt, m);
            mpz_add(N, N, D);
            mpz_mod(N, N, q);

            //D' = N + Dm in F_q
            mpz_mul(D, Dt, m);
            mpz_add(D, Nt, D);
            mpz_mod(D, D, q);
        }
    }
    mpz_gcdext(Nt, Dt, temp, D, q);
    mpz_mod(Dt, Dt, q);

    if (mpz_cmp_ui(Nt, 1) == 0) {
        rop->inf = false;
        mpz_mul(temp, Dt, N);
        mpz_mod(rop->value, temp, q);
    } else if (mpz_cmp(Nt, q) != 0) {
        gmp_printf("%Zd is a factor of n", Nt);
        exit(EXIT_FAILURE);
    } else {
        param_set_inf(rop);
    }
    mpz_clears(N, D, Nt, Dt, NULL);
}

int main() {
    // Initialize the random state
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, arc4random());

    keys_f ks;
    mpz_t e;
    mpz_inits(e, NULL);
    param_t res1, res2;
    param_inits(&res1, &res2,NULL);

    fast_keys_init(&ks);

    for (int i = 0; i < 100; i++) {
        fast_piso_gen(&ks, 512, state);
        rand_range_ui(e, state, 2, ks.pk.q);
        mod_more_mpz_old(&res1, ks.pk.g, e, ks.pk.d, ks.pk.q);
        mod_more_mpz(&res2, ks.pk.g, e, ks.pk.d, ks.pk.q);

        if (mpz_cmp(res1.value, res2.value) != 0) {
            gmp_printf("Error: mod_more_mpz and mod_more_mpz_old are not equal\n %s\n %s\n", param_get_str(res1), param_get_str(res2));
            exit(EXIT_FAILURE);
        }
    }
}