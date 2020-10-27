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
#include "../data/trie.h"
#include "errors.h"
#include <time.h>
#include "utils.h"

void fill_trie(Trie trie, char* dict, enum language lang) {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE* fp;
    clock_t start = clock();

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

        parse_word(line);
        insert_word(trie, line, lang, 0);
    	
    }

    fclose(fp);
    free(line);

    if (fprintf(stdout, "Successfully loaded %s into trie in %f s.\n", dict, (double)(clock() - start) / CLOCKS_PER_SEC) < 0)
        print_perr();
	
}

void construct_dawg(char* dict) {
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
