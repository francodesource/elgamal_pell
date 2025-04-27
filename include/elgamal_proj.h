//
// Created by fvfra on 27/04/2025.
//

#ifndef ELGAMAL_PROJ_H
#define ELGAMAL_PROJ_H

#include <gmp.h>

#include "keys.h"
#include "ciphertext.h"

keys proj_gen(mp_bitcnt_t n, gmp_randstate_t state);

ciphertext proj_enc(const mpz_t msg, const public_key pk, gmp_randstate_t state);

void proj_dec(mpz_t rop, const ciphertext ct, const public_key pk, const secret_key _sk);
#endif //ELGAMAL_PROJ_H
