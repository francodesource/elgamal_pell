//
// Created by fvfra on 14/04/2025.
//

typedef struct {
    char * c1;
    char * c2;
    char * d;
} ciphertext;

void chiphertext_from(ciphertext *ct, param_t c1, param_t c2, mpz_t d){
    ct->c1 = param_get_str(c1);
    ct->c2 = param_get_str(c2);
    ct->d = mpz_get_str(NULL, 16, d);
}

void ciphertext_print(ciphertext ct) {
    printf("ciphertext:\nc1: %s\nc2: %s\nd: %s\n", ct.c1, ct.c2, ct.d);
}