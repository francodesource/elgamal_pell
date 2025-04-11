//
// Created by fvfra on 11/04/2025.
//

float timer() {
    return (float) clock() / CLOCKS_PER_SEC;
}

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

/**
* Stores in rop the smallest non-square mod q
* @param rop stores the result, must be already initialized
* @param q the modulus, must be already initialized
*/
void smallest_non_square(mpz_t rop, const mpz_t q) {
    mpz_set_ui(rop, 2);
    while (mpz_jacobi(rop, q) != -1) {
        mpz_add_ui(rop, rop, 1);
    }
}
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