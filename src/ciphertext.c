//
// Created by fvfra on 14/04/2025.
//

typedef struct {
    char * c1;
    char * c2;
    char * d;
} ciphertext;

void chiphertext_from(ciphertext *ct, mpz_t c1, mpz_t c2, mpz_t d){
    ct->c1 = mpz_get_str(NULL, 16, c1);
    ct->c2 = mpz_get_str(NULL, 16, c2);
    ct->d = mpz_get_str(NULL, 16, d);
}

void ciphertext_print(ciphertext ct) {
    printf("ciphertext:\nc1: %s\nc2: %s\nd: %s\n", ct.c1, ct.c2, ct.d);
}