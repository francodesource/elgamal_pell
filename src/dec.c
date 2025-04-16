//
// Created by fvfra on 14/04/2025.
//

void dec(mpz_t rop, const ciphertext ct, const public_key pk, const secret_key _sk, int t) {
    mpz_t x, y, d1, q, sk;
    param_t c1, c2, m; // c1 and c2 must  not be modified inside the loop

    param_inits(&c1, &c2, &m, NULL);
    mpz_inits(x, y, d1, q, sk, NULL);

    ciphertext_set(&c1, &c2, d1, ct);
    mpz_set_str(sk, _sk, 16);
    mpz_set_str(q, pk.q, 16);
    unsigned long n = mpz_sizeinbase(q, 2);
    unsigned long pad = padding(n);

    float t_dec[t];
    for (int i = 0; i < t; i++) {
        float start = timer();
        mod_more(&m, &c1, sk, d1, q);
        param_invert(&m, &m, q);
        param_op(&m, &m, &c2, d1, q); // (-c1^sk) * c2

        param_coord(x, y, &m, d1, q);
        mpz_tdiv_q_2exp(x, x, pad);
        mpz_mul_2exp(rop, x, n - 1);
        mpz_sub_ui(y, y, 1);
        mpz_add(rop, rop, y);

        t_dec[i] = timer() - start;
    }
    if (t > 1) {
        char filepath[100];
        sprintf(filepath, "%s/elgamal_piso_%ld_%d", results_folder_location(), n, t);
        FILE * file =  fopen(filepath, "a");
        fprintf(file, "*** Dec(%ld, %d) ***\ntime(dec)\t%f\n\n",n, t, min(t_dec, t));
        fclose(file);
    }
    mpz_clears(x, y, d1, q, sk, NULL);
    param_clears(&c1, &c2, &m, NULL);
}
