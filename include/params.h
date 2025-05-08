//
// Created by fvfra on 25/04/2025.
//

#ifndef PARAMS_H
#define PARAMS_H
#include <gmp.h>
#include <stdbool.h>
/**
 * Represents an element of the parametrized Pell Hyperbola
 * that can be infinite or a number in F_q
 */
typedef struct {
    bool inf;
    mpz_t value;
} param_t;

void param_init(param_t * op);

void param_inits(param_t * first, ...);

void param_clear(param_t * op);

void param_clears(param_t * first, ...);

char* param_get_str(const param_t param);

void param_set_inf(param_t *param);

void param_set(param_t *rop, const param_t *op);

void param_set_str(param_t *rop, const char* str, const int base);

void param_set_mpz(param_t *rop, const mpz_t op);

void param_invert(param_t *rop, const param_t *op, const mpz_t mod);

void param_op_mpz(param_t * rop, const param_t * m1, const mpz_t m2, const mpz_t d, const mpz_t q);

void param_op(param_t * rop, const param_t * m1, const param_t * m2, const mpz_t d, const mpz_t q);

void mod_more_mpz(param_t * rop, const mpz_t m, const mpz_t e, const mpz_t d, const mpz_t q);

void mod_more(param_t * rop, const param_t * m, const mpz_t e, const mpz_t d, const mpz_t q);

void param_coord(mpz_t x, mpz_t y, const param_t * m, const mpz_t d, const mpz_t mod);
#endif //PARAMS_H
