//
// Created by fvfra on 11/04/2025.
//

/**
 *  Stores in rop a generated pseudo-random number within given range [min, max)
 *  all parameters must be already initialized
 *
 * @param rop stores the result, a pseudo-random number
 * @param state the random state, must be already initialized
 * @param min an unsigned integer, the lower bound
 * @param max a mpz, the upper bound
 */
void rand_range_ui(mpz_t rop, gmp_randstate_t state, const unsigned long min, const mpz_t max) {
    mpz_t upper_bound;
    mpz_init(upper_bound);
    mpz_sub_ui(upper_bound, max, min);

    mpz_urandomm(rop, state, upper_bound);
    mpz_add_ui(rop, rop, min);
    mpz_clear(upper_bound);
}

/**
 * Stores in rop a generated pseudo-random number with given size (in range [2^(bits-1), 2^bits)
 * all parameters must be already initialized
 * @param rop stores the result
 * @param state random state
 * @param bits the desired size in bits
 */
void rand_bit_size(mpz_t rop, gmp_randstate_t state, const mp_bitcnt_t bits) {
    mpz_urandomb(rop, state, bits);
    mpz_setbit(rop, bits-1);
}

/**
 * Stores in rop a generated pseudo-random prime number with given size (in range [2^(n-bits), 2^bits)
 * the result will be a number that is probably a prime
 * all parameters must be already initialized
 *
 * @param rop stores the result
 * @param state random state
 * @param bits the desired size in bits
 */
void rand_prime(mpz_t rop, gmp_randstate_t state, const mp_bitcnt_t bits) {
    rand_bit_size(rop, state, bits);
    mpz_nextprime(rop, rop);

    if (mpz_sizeinbase(rop, 2) > bits)
        mpz_prevprime(rop, rop);
}

/**
 * Stores in q and p two probably prime numbers such that q = 2*p - 1, where q has size equal to bits
 * all parameters must be already initialized
 *
 * @param q stores q
 * @param p stores p
 * @param state random state
 * @param bits the size of q in bits
 */
void rand_prime_q_p(mpz_t q, mpz_t p, gmp_randstate_t state, const mp_bitcnt_t bits) {
    do {
        rand_prime(p, state, bits - 1);
        mpz_mul_ui(q, p, 2);
        mpz_sub_ui(q, q, 1);
    } while (mpz_probab_prime_p(q, 15) == 0);
}