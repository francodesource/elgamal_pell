#include <stdio.h>
#include <gmp.h>

int main(void) {
    mpz_t googol;
    mpz_init_set_ui(googol, 10);
    mpz_pow_ui(googol, googol, 100);
    gmp_printf("Hello Googol! %Zd\n", googol);
    return 0;
}