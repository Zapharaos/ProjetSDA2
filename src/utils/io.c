/*
 * Copy this function template to construct either a DAWG or a trie
 * based on the dictionary filename given
 *
 * Don't forget to change the void return type of this function
 */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void construct(char* dict) {
    // Instantiate either a Trie or a DAWG here
    // ...

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE* fp;

    // open file 
    fp = fopen(dict, "r"); // read mode
    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    // read file
    while ((read = getline(&line, &len, fp)) != -1) {
        // remove newline
        size_t length = strlen(line);
        if ((length > 0) && (line[length - 1] == '\n'))
        {
            line[length - 1] = '\0';
        }

        // here insert the word in the trie or in the DAWG
        // To complete ... 
    }

    fclose(fp);
    free(line);

    // return ...;
}
