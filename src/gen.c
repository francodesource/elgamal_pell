//
// Created by fvfra on 11/04/2025.
//

typedef struct {
    public_key pk;
    secret_key sk;
} keys;

keys gen(mp_bitcnt_t n, int t, gmp_randstate_t state) {
    mpz_t g, q, p, d, sk;
    mpz_inits(g, q, p, d, sk, NULL);

    param_t h;
    param_init(&h);

    float t_par[t], t_mul[t];
    if (!primes_q_p_by_size(q, p, n)) {
        rand_prime_q_p(q, p, state, n);
    }
    // finding minimum time in t iterations
    for (int i = 0; i < t; i++) {

        // measuring time for parameter generation
        float start = timer();
        smallest_non_square(d, q);

        rand_primitive_root(g, state, d, q, p);
        printf("here\n");
        t_par[i] = timer() - start;

        // measuring time for exponentiation
        start = timer();
        rand_range_ui(sk, state, 2, q);
        mod_more_mpz(&h, g, sk, d, q);
        t_mul[i] = timer() - start;
    }

    // TODO: writing to file...

    // returning the key as hex strings
    keys res;
    public_key_from(&res.pk, q, d, g, h.value);
    secret_key_from(&res.sk, sk);
    return res;

}