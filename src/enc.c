//
// Created by fvfra on 14/04/2025.
//

ciphertext enc(const mpz_t msg, const public_key pk, gmp_randstate_t state, int t) {
    mpz_t q, d, d1, g, h, x, y, m, s, r, tmp;
    mpz_inits(q, d, d1, g, h, x, m, y,s, r, tmp, NULL);
    param_t c1, c2;
    param_init(&c1);
    param_init(&c2);
    public_key_set(q, d, g, h, pk); // converting form hexadecimal to mpz_t
    // computing padding value
    unsigned long q_bits = mpz_sizeinbase(q, 2);
    unsigned long pad = q_bits / 16;
    // check if message has correct size
    if (mpz_sizeinbase(msg, 2) > 2 * (q_bits - 1) - pad) {
        perror("Error: message is too long\n");
        exit(EXIT_FAILURE);
    }

    float t_enc[t];
    for (int i = 0; i < t; i++) {
        float start = timer();
        // splitting message in two coordinates
        mpz_tdiv_q_2exp(x, msg, q_bits - 1);
        // padding the message
        mpz_mul_2exp(x, x, pad);
        // finding a suitable d
        bool found = false;
        for (unsigned long int j = 0; j < pad; j++) {
            mpz_mul(d1, x, x);
            mpz_sub_ui(d1, d1, 1);
            mpz_mod(d1, d1, q);
            if (mpz_jacobi(d1, q) == -1) {
                found = true;
                break;
            }
            mpz_add_ui(x, x, 1);
        }

        // exit the program if no suitable d is found
        if (!found) {
            perror("Error: non square d found\n");
            exit(EXIT_FAILURE);
        }
        // setting y
        mpz_tdiv_r_2exp(y, msg, q_bits - 1);
        if (mpz_invert(y, y, q) == 0) { // y <- y^-1
            gmp_fprintf(
                stderr,
                "Error: y (%Zd) is not invertible\n",
                y
                );
            exit(EXIT_FAILURE);
        }
        //  setting d
        mpz_powm_ui(tmp, y, 2, q); // tmp <- y^2
        mpz_mul(d1, d1, tmp);
        mpz_mod(d1, d1, q); // d1 <- (x^2 - 1) / y^2

        // setting m
        mpz_add_ui(m, x, 1);
        mpz_mul(m, m, y);
        mpz_mod(m, m, q);
        // setting random exponent r
        rand_range_ui(r, state, 2, q);

        // setting s

        mpz_invert(d, d, q);
        mpz_mul(tmp, d, d1); // tmp <- d^-1 * d1
        mpz_mod(tmp, tmp, q);

        sqrt_m(s, tmp, q);

        // setting c1 & c2
        mpz_mul(g, g, s);
        mpz_mod(g, g, q);

        mpz_mul(h, h, s);
        mpz_mod(h, h, q);

        mod_more_mpz(&c1, g, r, d1, q);
        mod_more_mpz(&c2, h, r, d1, q);
        param_op_mpz(&c2, &c2, m, d1, q);
        t_enc[i] = timer() - start; // getting time
    }

    if (t > 1) {
        char filepath[100];
        sprintf(filepath, "%s/elgamal_piso_%ld_%d", results_folder_location(), q_bits, t);
        FILE *fp = fopen(filepath, "a");

        fprintf(fp, "*** Enc(%ld, %d) ***\n", q_bits, t);
        fprintf(fp, "time(enc)%f\n", min(t_enc, t));
        fclose(fp);
    }

    const ciphertext ct = {
        .c1 = param_get_str(c1),
        .c2 = param_get_str(c2),
        .d  = mpz_get_str(NULL, 16, d1)
    };

    // freeing memory
    mpz_clears(q, d, d1, g, h, x, m, s, r, tmp, c1.value, c2.value, NULL);
    return ct;
}