#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/keys.h"
#include "include/elgamal_piso.h"
#include "include/elgamal_proj.h"

// Modify these parameters to test different sizes and iterations
#define SIZE 1024
#define MSG "123456"

int main(void) {
    // initializing the random state
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, arc4random());

    mpz_t msg, res;
    mpz_inits(msg, res, NULL);
    mpz_set_str(msg, "123456", 10);

    keys ks = piso_gen(SIZE, state);
    public_key_print(ks.pk);
    printf("Secret key: %s\n", ks.sk);


    gmp_printf("Encrypting now message: %Zd\n", msg);
    ciphertext_d ct = piso_enc(msg, ks.pk, state);
    ciphertext_d_print(ct);

    piso_dec(res, ct, ks.pk, ks.sk);
    gmp_printf("Decrypted message: %Zd\n", res);

    if (mpz_cmp(msg, res) != 0) {
        perror("elgamal piso failed\n");
    }
    mpz_set_str(msg, "24681214", 10);
    ks = proj_gen(SIZE, state);
    public_key_print(ks.pk);
    ciphertext ct2 = proj_enc(msg, ks.pk, state);
    ciphertext_print(ct2);
    proj_dec(res, ct2, ks.pk, ks.sk);
    gmp_printf("Decrypted message: %Zd\n", res);
    if (mpz_cmp(msg, res) != 0) {
        perror("elgamal proj failed\n");
    }

    // cleaning
    mpz_clears(msg, res, NULL);
    public_key_clear(&ks.pk);
    secret_key_clear(ks.sk);
    ciphertext_d_clear(&ct);
    ciphertext_clear(&ct2);

    gmp_randclear(state);
    return 0;
}