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
        t_par[i] = timer() - start;

        // measuring time for exponentiation
        start = timer();
        rand_range_ui(sk, state, 2, q);
        mod_more_mpz(&h, g, sk, d, q);
        t_mul[i] = timer() - start;
    }

    char filepath[100];
    char * result_folder = results_folder_location();
    sprintf(filepath, "%s/elgamal_piso_%ld_%d", result_folder, n, t);
    // cleaning file
    FILE *fp = fopen(filepath, "w");
    fprintf(fp, "%s", "");
    fclose(fp);
    // writing to file
    fp = fopen(filepath, "a");
    fprintf(fp, "*** Gen(%ld, %d) ***\ntime(par)%f\ntime(mul)%f\n", n, t, min(t_par, t), min(t_mul, t));
    fclose(fp);

    // returning the key as hex strings
    keys res;
    public_key_from(&res.pk, q, d, g, h.value);
    secret_key_from(&res.sk, sk);
    return res;

}