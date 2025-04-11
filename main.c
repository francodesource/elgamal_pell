#include <stdio.h>
#include <gmp.h>

#include "src/keys.c"

int main(void) {
    public_key public_key;
    mpz_t n, q, d, g, h;
    mpz_inits(n, q, d, g, h, NULL);
    mpz_set_str(n, "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", 10);
    mpz_set_str(q, "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", 10);
    mpz_set_str(d, "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", 10);
    mpz_set_str(g, "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", 10);
    mpz_set_str(h, "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", 10);
    public_key_from(&public_key, q, d, g, h);
    secret_key private_key;
    secret_key_from(&private_key, n);
    printf("Public Key:\n");
    printf("q: %s\n", public_key.q);
    printf("d: %s\n", public_key.d);
    printf("g: %s\n", public_key.g);
    printf("h: %s\n", public_key.h);
    printf("Private Key:\n");
    printf("n: %s\n", private_key);

    return 0;
}