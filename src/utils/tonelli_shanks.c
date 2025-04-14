//
// Created by fvfra on 14/04/2025.
//

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