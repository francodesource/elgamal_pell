//
// Created by fvfra on 11/04/2025.
//

/**
 * A pair of public and secret keys for the ElGamal PISO scheme
 * where parameters are stored in hexadecimal format.
 */
typedef struct {
    public_key pk;
    secret_key sk;
} keys;

/**
 * Generates the keys for the ElGamal PISO scheme:
 *  - q = 2p - 1 where q and p are prime
 * @param n the desired size of q in bits
 * @param t the number of iterations for the time measurement
 * @param state the random state used for random number generation
 * @return a private key and a public key
 */
keys gen(mp_bitcnt_t n, int t, gmp_randstate_t state) {
    mpz_t g, q, p, d, sk;
    mpz_inits(g, q, p, d, sk, NULL);

    param_t h;
    param_init(&h);

    float t_par[t], t_mul[t];
    if (!primes_q_p_by_size(q, p, n)) {
        // if there are no primes of size n, we generate them
        rand_prime_q_p(q, p, state, n);
    }
    // finding minimum time in t iterations
    for (int i = 0; i < t; i++) {

        // measuring time for parameter generation
        float start = timer();
        smallest_non_square(d, q);
        rand_primitive_root(g, state, d, q, p);
        t_par[i] = timer() - start;

        // measuring time for exponentiation
        start = timer();
        rand_range_ui(sk, state, 2, q);
        mod_more_mpz(&h, g, sk, d, q);
        t_mul[i] = timer() - start;
    }

    // printing time on file only for more than one iteration
    if (t > 1) {
        char filepath[100];
        char * result_folder = results_folder_location();
        sprintf(filepath, "%s/elgamal_piso_%ld_%d", result_folder, n, t);

        // writing to file
        FILE * fp = fopen(filepath, "a");
        fprintf(fp, "*** Gen(%ld, %d) ***\ntime(par)\t%f\ntime(mul)\t%f\n", n, t, min(t_par, t), min(t_mul, t));
        fclose(fp);
    }

    // returning the key as hex strings
    keys res;
    public_key_from(&res.pk, q, d, g, h);
    secret_key_from(&res.sk, sk);

    // freeing memory
    mpz_clears(g, q, p, d, sk, NULL);
    param_clears(&h, NULL);

    return res;

}