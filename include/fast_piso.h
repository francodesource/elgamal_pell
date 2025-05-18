//
// Created by fvfra on 07/05/2025.
//

#ifndef FAST_PISO_H
#define FAST_PISO_H

#include <gmp.h>

#include "./fast_keys.h"
#include "./fast_cipher.h"

/**
 * Generates the keys for the ElGamal PISO scheme:
 *  - q = 2p - 1 where q and p are prime
 * @param n the desired size of q in bits
 * @param state the random state used for random number generation
 * @return a private key and a public key
 */
void fast_piso_gen(keys_f * ks, mp_bitcnt_t n, gmp_randstate_t state);

/**
 * Encrypts a message using the ElGamal PISO scheme
 * @param msg the message to encrypt
 * @param pk the public key
 * @param state the random state
 * @return the ciphertext
 */
void fast_piso_enc(ciphertext_f * ct, const mpz_t msg, const public_key_f * pk, gmp_randstate_t state);

void fast_piso_dec(mpz_t rop, const ciphertext_f * ct, const keys_f * ks);
#endif //FAST_PISO_H
