//
// Created by fvfra on 27/04/2025.
//

#ifndef ELGAMAL_PROJ_H
#define ELGAMAL_PROJ_H

#include <gmp.h>

#include "keys.h"

keys proj_gen(mp_bitcnt_t n, gmp_randstate_t state);
#endif //ELGAMAL_PROJ_H
