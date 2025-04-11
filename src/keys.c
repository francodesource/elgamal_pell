//
// Created by fvfra on 11/04/2025.
//

typedef struct {
    char *q;
    char *d;
    char *g;
    char *h;
} public_key;

typedef char* secret_key;

void public_key_from(public_key *pk, mpz_t q, mpz_t d, mpz_t g, mpz_t h){
    pk->q = mpz_get_str(NULL, 16, q);
    pk->d = mpz_get_str(NULL, 16, d);
    pk->g = mpz_get_str(NULL, 16, g);
    pk->h = mpz_get_str(NULL, 16, h);
}

void secret_key_from(secret_key *sk, mpz_t n){
    *sk = mpz_get_str(NULL, 16, n);
}