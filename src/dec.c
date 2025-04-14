//
// Created by fvfra on 14/04/2025.
//

void dec(mpz_t rop, const ciphertext ct, const public_key pk, const secret_key _sk, int t) {
    mpz_t x, y, d1, q, sk;
    param_t c1, c2, m;
    //TODO create variadic function to init multiple params
    param_init(&c1);
    param_init(&c2);
    param_init(&m);

    mpz_inits(x, y, d1, q, sk, NULL);

    ciphertext_set(&c1, &c2, d1, ct);
    mpz_set_str(sk, _sk, 16);
    mpz_set_str(q, pk.q, 16);
    unsigned long n = mpz_sizeinbase(q, 2);
    unsigned long pad = n / 16;

    float t_dec[t];
    for (int i = 0; i < t; i++) {
        mod_more(&c1, &c1, sk, d1, q);
        param_invert(&c1, &c1, q);
        param_op(&m, &c1, &c2, d1, q); // (-c1^sk) * c2
        param_coord(x, y, &m, d1, q);
        mpz_tdiv_q_2exp(x, x, pad);
        mpz_mul_2exp(rop, x, n - 1);

        mpz_add(rop, rop, y);
        t_dec[i] = mpz_get_d(rop);
    }

    //TODO write to file

    mpz_clears(x, y, d1, q, sk, NULL);
    //TODO free params
}
