//
// Created by fvfra on 25/04/2025.
//

#ifndef ELGAMAL_PISO_H
#define ELGAMAL_PISO_H

#include <gmp.h>

#include "./keys.h"
#include "./ciphertext.h"

/**
 * Returns the padding size for the message given the size of q
 * @param size the size of q in bits
 * @return the number of bits to pad
 */
unsigned long padding(unsigned long size);

/**
 * Generates the keys for the ElGamal PISO scheme:
 *  - q = 2p - 1 where q and p are prime
 * @param n the desired size of q in bits
 * @param t the number of iterations for the time measurement
 * @param state the random state used for random number generation
 * @return a private key and a public key
 */
keys piso_gen(mp_bitcnt_t n, int t, gmp_randstate_t state);

/**
 * Encrypts a message using the ElGamal PISO scheme
 * @param msg the message to encrypt
 * @param pk the public key
 * @param state the random state
 * @param t the number of iterations for time measurement
 * @return the ciphertext
 */
ciphertext piso_enc(const mpz_t msg, const public_key pk, gmp_randstate_t state, int t);

void piso_dec(mpz_t rop, const ciphertext ct, const public_key pk, const secret_key _sk, int t);

#endif //ELGAMAL_PISO_H
