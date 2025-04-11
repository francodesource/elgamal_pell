#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "src/keys.c"
#include "src/params.c"
#include "src/utils/utils.c"
#include "src/utils/pq_con.c"
#include "src/gen.c"

int main(void) {
    const pq pqs = {"1232132", "121232"};

    printf("p: %s\n", pqs.p);
    return 0;
}