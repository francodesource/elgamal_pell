#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "results/location.c"
#include "src/params.c"
#include "src/keys.c"
#include "src/utils/utils.c"
#include "src/utils/pq_con.c"
#include "src/utils/tonelli_shanks.c"
#include "src/ciphertext.c"

#include "src/gen.c"
#include "src/enc.c"
#include "src/dec.c"

# define SIZE 512
# define ITER 10

int main(void) {
    // initializing the random state
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, arc4random());

    keys ks = gen(SIZE, ITER, state);
    public_key_print(ks.pk);
    printf("Secret key: %s\n", ks.sk);

    mpz_t msg, res;
    mpz_inits(msg, res, NULL);
    mpz_set_str(msg, "123456", 10);

    gmp_printf("Encrypting now message: %s\n", mpz_get_str(NULL, 2, msg));
    ciphertext ct = enc(msg, ks.pk, state, ITER);
    ciphertext_print(ct);

    dec(res, ct, ks.pk, ks.sk, ITER);
    gmp_printf("Decrypted message: %Zd\n", res);

    if (mpz_cmp(msg, res) != 0) {
        perror("elgamal piso failed :(\n");
    }

    return 0;
}