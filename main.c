#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "results/location.c"
#include "src/keys.c"
#include "src/params.c"
#include "src/utils/utils.c"
#include "src/utils/pq_con.c"
#include "src/utils/tonelli_shanks.c"
#include "src/gen.c"


int main(void) {
    // initializing the random state
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, arc4random());

    keys ks = gen(7680, 100, state);

    public_key_print(ks.pk);
    printf("Secret key: %s\n", ks.sk);
    printf("Results folder: %s\n", results_folder_location());
    return 0;
}