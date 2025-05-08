//
// Created by fvfra on 07/05/2025.
//

#ifndef FAST_KEYS_H
#define FAST_KEYS_H

#include <gmp.h>

#include "params.h"

typedef struct {
  mpz_t q, d, g;
  param_t h;
} public_key_f;

typedef mpz_t secret_key_f;

typedef struct {
  public_key_f pk;
  secret_key_f sk;
} keys_f;

void public_key_f_init(public_key_f *pk);
void public_key_f_clear(public_key_f *pk);
void fast_keys_init(keys_f *ks);
void fast_keys_clear(keys_f *ks);
void fast_keys_print(keys_f *ks);
#endif //FAST_KEYS_H
