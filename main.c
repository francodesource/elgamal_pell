#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "src/keys.c"
#include "src/params.c"
#include "src/utils/utils.c"
#include "src/utils/pq_con.c"
#include "src/gen.c"

int main(void) {
    // initializing the random state
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, arc4random());
    mpz_t p, q, d, rop;
    mpz_inits(p, q, d, rop, NULL);
    mpz_set_str(p, "6474160844665141580548654534765504308838085219070930577434944058815797462566748402058060921424417426605357283897923169808918807444883299382439729068484427", 10);
    mpz_set_str(q, "12948321689330283161097309069531008617676170438141861154869888117631594925133496804116121842848834853210714567795846339617837614889766598764879458136968853", 10);
    mpz_set_str(d, "5040621820071458079897780130299380946220830422592283845117085003230491064329337346982776752699414385077866740932522006070223255963185580385249112067564900", 10);
    // mpz_set_str(rop, "6045620645015437302842817890203099066357499493256384824823308855567955292364427156260332314856219226349968283355896722528280751805244580608717554753141116", 10);


    rand_primitive_root(rop, state, d, q, p);
    // print rop
    gmp_printf("primitive root: %Zd\n", rop);
    param_t param;
    param_init(&param);
    mpz_mul_ui(p, p, 2);
    mod_more_mpz(&param, rop, p, d, q);

    // print param
    if (param.inf) {
        printf("inf\n");
    } else {
        gmp_printf("param: %Zd\n", param.value);
    }

    // keys ks = gen(512, 10, state);
    // // print keys:
    // printf("Public Key:\n");
    // printf("q: %s\n", ks.pk.q);

    return 0;
}