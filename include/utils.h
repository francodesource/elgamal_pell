//
// Created by fvfra on 25/04/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include <gmp.h>


float timer();

/**
 *  Stores in rop a generated pseudo-random number within given range [min, max)
 *  all parameters must be already initialized
 *
 * @param rop stores the result, a pseudo-random number
 * @param state the random state, must be already initialized
 * @param min an unsigned integer, the lower bound
 * @param max a mpz, the upper bound
 */
void rand_range_ui(mpz_t rop, gmp_randstate_t state, const unsigned long min, const mpz_t max);

/**
 * Stores in rop a generated pseudo-random number with given size (in range [2^(bits-1), 2^bits)
 * all parameters must be already initialized
 * @param rop stores the result
 * @param state random state
 * @param bits the desired size in bits
 */
void rand_bit_size(mpz_t rop, gmp_randstate_t state, const mp_bitcnt_t bits);

/**
 * Stores in rop a generated pseudo-random prime number with given size (in range [2^(n-bits), 2^bits)
 * the result will be a number that is probably a prime
 * all parameters must be already initialized
 *
 * @param rop stores the result
 * @param state random state
 * @param bits the desired size in bits
 */
void rand_prime(mpz_t rop, gmp_randstate_t state, const mp_bitcnt_t bits);

/**
 * Stores in q and p two probably prime numbers such that q = 2*p - 1, where q has size equal to bits
 * all parameters must be already initialized
 *
 * @param q stores q
 * @param p stores p
 * @param state random state
 * @param bits the size of q in bits
 */
void rand_prime_q_p(mpz_t q, mpz_t p, gmp_randstate_t state, const mp_bitcnt_t bits);

/**
 * Returns a random non-square mod q
 *
 * @param rop stores the result, must be already initialized
 * @param state the random state
 * @param q the modulus, must be already initialized
 */
void rand_non_square(mpz_t rop, gmp_randstate_t state, const mpz_t q);
/**
* Stores in rop the smallest non-square mod q
* @param rop stores the result, must be already initialized
* @param q the modulus, must be already initialized
*/
void smallest_non_square(mpz_t rop, const mpz_t q);

/**
* Stores in rop a random generator of order q + 1.
* All parameters must be already initialized.
*
* @param rop stores the result
* @param state the random state
* @param d the d parameter of the hyperbola
* @param q a prime number such that q = 2*p + 1
* @param p a prime number
*/
void rand_primitive_root(mpz_t rop, gmp_randstate_t state, const mpz_t d, const mpz_t q, const mpz_t p);

/**
 * Returns the minimum value in a vector of floats
 */
float min(const float * vec,const int size);

int sqrt_m(mpz_t rop, const mpz_t op, const mpz_t p);
#endif //UTILS_H
