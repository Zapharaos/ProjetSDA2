#include "erros.h"

void err_print() {
    perror("fprintf failed"); //exception use of perror
    exit(1);
}

void pas_content(char *message) {
    if (fprintf(stderr, "%s", message) < 0)
        err_print();
    exit(1);
}
