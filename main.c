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
# define ITER 1

int main(void) {
    // initializing the random state
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, arc4random());

    keys ks = gen(SIZE, ITER, state);



    ks.pk.q = "f73a13fa6ea07aee66ce4ea9b45cdcd91834c257fff33e69f29b2212b2730b6bca0720abf2172e49710751d489d14c0850e05762b2639368e0c28dff7d974e95";
    ks.pk.d = "2";
    ks.pk.g = "471c5764dd045f2bd5ed89b19cdbfa1506a855cdfcfc1fb085364b32ac9090da067c7e0766341b58b60a0904950c3bcc426854227cd419b53b32bf71e2711c04";
    ks.pk.h = "138772f5197736b12d7f6fe82a6748def71e1c3204e0f935e41e2d003e41691b1cd11659294d5b1767f31a886cb477dec90cd19fbc0811ed7819387763e3344c";
    public_key_print(ks.pk);
    printf("Secret key: %s\n", ks.sk);

    mpz_t msg, res;
    mpz_inits(msg, res, NULL);
    //mpz_set_str(msg, "123456", 10);
    mpz_set_str(msg, ks.pk.q, 16);
    mpz_tdiv_q_ui(msg, msg, 100000*3);
    mpz_mul(msg, msg, msg);
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