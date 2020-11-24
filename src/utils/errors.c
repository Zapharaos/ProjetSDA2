#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

/**
 * An error was encountered
 */
void raler(char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

/**
 * Displays a message in stderr
 */
void print_error(char *message)
{
    if (fprintf(stderr, "%s\n", message) < 0)
        raler("fprintf");
}

/**
 * Displays a message in stdout
 */
void print_msg(char* message)
{
    if (fprintf(stdout, "%s\n", message) < 0)
        raler("fprintf");
}