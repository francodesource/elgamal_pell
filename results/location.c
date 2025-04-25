//
// Created by fvfra on 11/04/2025.
//
#include <string.h>
#include <stdlib.h>

char* results_folder_location() {
    char * res = malloc(100 *sizeof(char));
    char filepath[] = __FILE__;

    for (long i = strlen(filepath) - 1; i >= 0; --i) {
        if (filepath[i] == '/') {
            filepath[i] = '\0';
            break;
        }
    }
    strcpy(res, filepath);
    return res;

}