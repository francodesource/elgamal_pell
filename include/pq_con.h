//
// Created by fvfra on 25/04/2025.
//

#ifndef PQ_CON_H
#define PQ_CON_H
#include <gmp.h>
#include <stdbool.h>

bool primes_q_p_by_size(mpz_t q, mpz_t p, const mp_bitcnt_t size);
bool primes_q_d_g_by_size(mpz_t q, mpz_t d, mpz_t g, const mp_bitcnt_t size);
#endif //PQ_CON_H
