#include "errors.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * An error was encountered using frprintf
 */
void print_perr()
{
    perror("fprintf failed"); //exception use of perror
    exit(1);
}

/**
 * An error was encountered
 */
void print_err(char *message)
{
    if (fprintf(stderr, "%s\n", message) < 0)
        print_perr();
    exit(EXIT_FAILURE);
}

/**
 * Displays a message
 */
void print_msg(char* message)
{
    if (fprintf(stdout, "%s\n", message) < 0)
        print_err("Could not print error to stderr");
}
