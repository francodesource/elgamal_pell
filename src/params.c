//
// Created by fvfra on 11/04/2025.
//
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/params.h"

void param_init(param_t * op) {
    op->inf = false;
    mpz_init(op->value);
}

void param_inits(param_t * first, ...) {
    va_list args;
    va_start(args, first);

    param_t * current = first;
    while (current != NULL) {
        param_init(current);
        current = va_arg(args, param_t*);
    }
}

void param_clear(param_t * op) {
    mpz_clear(op->value);
}

void param_clears(param_t * first, ...) {
    va_list args;
    va_start(args, first);

    param_t * current = first;
    while (current != NULL) {
        mpz_clear(current->value);
        current = va_arg(args, param_t*);
    }
}


char* param_get_str(const param_t param) {
    if (param.inf) {
        return "inf";
    }
    return mpz_get_str(NULL, 16, param.value);
}

void param_set_inf(param_t *param) {
    param->inf = true;
}

void param_set(param_t *rop, const param_t *op) {
    if (op->inf) {
        param_set_inf(rop);
    } else {
        rop->inf = false;
        mpz_set(rop->value, op->value);
    }
}

void param_set_mpz(param_t *rop, const mpz_t op) {
    rop->inf = false;
    mpz_set(rop->value, op);
}

void param_set_str(param_t *rop, const char* str, const int base) {
    if (strcmp(str, "inf") == 0) {
        param_set_inf(rop);
    } else {
        rop->inf = false;
        mpz_set_str(rop->value, str, base);
    }
}

void param_invert(param_t *rop, const param_t *op, const mpz_t mod) {
    if (op->inf) {
        param_set_inf(rop);
        return;
    }
    rop->inf = false;
    mpz_neg(rop->value, op->value);
    mpz_mod(rop->value, rop->value, mod);
}

inline void param_op_mpz(param_t * rop, const param_t * m1, const mpz_t m2, const mpz_t d, const mpz_t q) {
    if (m1->inf) {
        param_set_mpz(rop, m2);
        return;
    }

    mpz_t sum;
    mpz_init(sum);
    mpz_add(sum, m1->value, m2);
    mpz_mod(sum, sum, q);

    if (mpz_cmp_ui(sum, 0) != 0) {
        rop->inf = false;
        mpz_invert(sum, sum, q);
        mpz_mul(rop->value, m1->value, m2);
        mpz_add(rop->value, rop->value, d);
        mpz_mul(rop->value, rop->value, sum);
        mpz_mod(rop->value, rop->value, q);

    } else {
        param_set_inf(rop);
    }

    mpz_clear(sum);
}

inline void param_op(param_t * rop, const param_t * m1, const param_t * m2, const mpz_t d, const mpz_t q) {
    // Here m2 can be inf too so we just need to check if m1 is inf
    // else we just run param_op_mpz

    if (m2->inf) {
        param_set(rop, m1);
        return;
    }

    // Here we know that m2 is not inf
    param_op_mpz(rop, m1, m2->value, d, q);
}

inline void mod_more_mpz(param_t * rop, const mpz_t m, const mpz_t e, const mpz_t d, const mpz_t q) {
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
        gmp_fprintf(stderr, "%Zd is a factor of n", Nt);
        exit(EXIT_FAILURE);
    } else {
        param_set_inf(rop);
    }
    mpz_clears(N, D, Nt, Dt, NULL);
}

inline void mod_more(param_t * rop, const param_t * m, const mpz_t e, const mpz_t d, const mpz_t q) {
    if (m->inf) {
        param_set_inf(rop);
        return;
    }
    // Here we know that m is not inf
    mod_more_mpz(rop, m->value, e, d, q);
}

void param_coord(mpz_t x, mpz_t y, const param_t * m, const mpz_t d, const mpz_t mod) {
    if (m->inf) {
        mpz_set_ui(x,1);
        mpz_set_ui(y,0);
        return;
    }

    mpz_t m_sqr;
    mpz_init(m_sqr);
    mpz_powm_ui(m_sqr, m->value, 2, mod);
    mpz_add(x, m_sqr, d);
    // from now on I store in m_sqrt (m^2 - d)^-1
    mpz_sub(m_sqr, m_sqr, d);
    mpz_invert(m_sqr, m_sqr, mod);

    mpz_mul(x, x, m_sqr);
    mpz_mod(x, x, mod);

    mpz_mul_ui(y, m->value, 2);
    mpz_mul(y, y,m_sqr);
    mpz_mod(y, y, mod);

    mpz_clear(m_sqr);
}