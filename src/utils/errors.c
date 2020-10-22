#include "errors.h"

void print_perr() {
    perror("fprintf failed"); //exception use of perror
    exit(1);
}

void print_err(char *message) {
    if (fprintf(stderr, "%s\n", message) < 0)
        print_perr();
    exit(1);
}

void print_msg(char* message)
{
    if (fprintf(stdout, "%s\n", message) < 0)
        print_err("Could not print error to stderr");
}
