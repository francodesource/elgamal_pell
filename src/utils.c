//
// Created by fvfra on 11/04/2025.
//
#include <gmp.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/params.h"
float timer() {
    return (float) clock() / CLOCKS_PER_SEC;
}

void rand_range_ui(mpz_t rop, gmp_randstate_t state, const unsigned long min, const mpz_t max) {
    mpz_t upper_bound;
    mpz_init(upper_bound);
    mpz_sub_ui(upper_bound, max, min);

    mpz_urandomm(rop, state, upper_bound);
    mpz_add_ui(rop, rop, min);
    mpz_clear(upper_bound);
}

void rand_bit_size(mpz_t rop, gmp_randstate_t state, const mp_bitcnt_t bits) {
    mpz_urandomb(rop, state, bits);
    mpz_setbit(rop, bits-1);
}

void rand_prime(mpz_t rop, gmp_randstate_t state, const mp_bitcnt_t bits) {
    rand_bit_size(rop, state, bits);
    mpz_nextprime(rop, rop);

    if (mpz_sizeinbase(rop, 2) > bits)
        mpz_prevprime(rop, rop);
}

void rand_prime_q_p(mpz_t q, mpz_t p, gmp_randstate_t state, const mp_bitcnt_t bits) {
    do {
        rand_prime(p, state, bits - 1);
        mpz_mul_ui(q, p, 2);
        mpz_sub_ui(q, q, 1);
    } while (mpz_probab_prime_p(q, 15) == 0);
}

void rand_non_square(mpz_t rop, gmp_randstate_t state, const mpz_t q) {
    do {
        mpz_urandomm(rop, state, q);
    } while (mpz_jacobi(rop, q) != -1);
}

void smallest_non_square(mpz_t rop, const mpz_t q) {
    mpz_set_ui(rop, 2);
    while (mpz_jacobi(rop, q) != -1) {
        mpz_add_ui(rop, rop, 1);
    }
}

void rand_primitive_root(mpz_t rop, gmp_randstate_t state, const mpz_t d, const mpz_t q, const mpz_t p) {
    param_t temp;
    param_init(&temp);
    mpz_t two;
    mpz_init_set_ui(two, 2);
    while (1){
        rand_range_ui(rop, state, 2, q);
        mod_more_mpz(&temp, rop, two, d, q);
        const bool cond_1 = temp.inf;
        mod_more_mpz(&temp, rop, p, d, q);
        const bool cond_2 = temp.inf;
        if (!cond_1 && !cond_2) {
            break;
        }
    }
    mpz_clears(temp.value, two, NULL);
}

float min(const float * vec,const int size) {
    float min = vec[0];
    for (int i = 1; i < size; ++i) {
        if (vec[i] < min) {
            min = vec[i];
        }
    }
    return min;
}

int sqrt_m(mpz_t rop, const mpz_t op, const mpz_t p){
    // case op = 0
    if (mpz_cmp_ui(op, 0) == 0){
        mpz_set_ui(rop, 0);
        return 0;
    }
    // case p = 2
    if (mpz_cmp_ui(p, 2) == 0){
        mpz_set(rop, op);
        return 0;
    }
    // case op is not a square mod p
    if (mpz_jacobi(op, p) != 1){
        return -1;
    }
    // simple case (p = 3 mod 4)
    mpz_mod_ui(rop, p, 4);
    if (mpz_cmp_ui(rop, 3) == 0){
        mpz_add_ui(rop, p, 1);
        mpz_fdiv_q_ui(rop, rop, 4);
        mpz_powm(rop, op, rop, p);
        return 0;
    }

    mpz_t tmp, q, z, c, t, r, b;
    mpz_inits(tmp, q, z, c, t, r, b, NULL);

    // finding s and q such that p - 1 = q * 2^s
    mp_bitcnt_t s = 1;
    mpz_sub_ui(tmp, p, 1);
    while(1){
        if (mpz_divisible_2exp_p(tmp, s)){
            mpz_div_2exp(q, tmp, s);
            if (mpz_odd_p(q)) break;
        }
        s++;
    }

    // finding non quadratic residue z mod p
    mpz_set_ui(z, 2);
    while (mpz_jacobi(z, p) != -1) mpz_add_ui(z, z, 1);
    // setting r exponent in tmp
    mpz_add_ui(tmp, q, 1);
    mpz_fdiv_q_ui(tmp, tmp, 2);

    //initializing values
    mpz_powm(c, z, q, p);
    mpz_powm(t, op, q, p);
    mpz_powm(r, op, tmp, p);

    //loop
    while(1){
        mpz_set(tmp, t);
        // finding least i such that t^2^i = 1
        long unsigned int i;
        for(i = 0; i < s; i++){
            if (mpz_cmp_ui(tmp, 1) == 0)
                break;
            mpz_powm_ui(tmp, tmp, 2, p);
        }
        // exit condition
        if (i == 0){
            mpz_set(rop, r);
            mpz_clears(tmp, q, z, c, t, r, b, NULL);
            return 0;
        }

        mpz_ui_pow_ui(tmp, 2, s - i - 1);
        mpz_powm(b, c, tmp, p);

        // updating values
        s = i;
        mpz_powm_ui(c, b, 2, p);

        mpz_mul(t, t, c);
        mpz_mod(t, t, p);

        mpz_mul(r, r, b);
        mpz_mod(r, r, p);
    }
}