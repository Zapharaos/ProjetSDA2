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

/**
 * Creates a structure and stores a dictionnary
 */
void fill_trie(Trie trie, char* dict, enum language lang) {

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE* fp;
    clock_t start = clock();

    // open : file given as paramater (i.e. a dictionnary)
    if ((fp = fopen(dict, "r")) == NULL)
        print_err("fopen fill_trie");

    // read : file given as paramater (i.e. a dictionnary)
    while ((read = getline(&line, &len, fp)) != -1) {
        // remove newline
        size_t length = strlen(line);
        if ((length > 0) && (line[length - 1] == '\n'))
        {
            line[length - 1] = '\0';
        }

        // parsing the word
        parse_word(line);

        // insert : word inside the Trie structure given as paramater
        insert_word_trie(trie, line, lang, 0);
    }

    // free : line
    free(line);
    
    // close : file given as paramater (i.e. a dictionnary)
    if(fclose(fp) != 0)
        print_err("fclose fill_trie");

    // print : success + time needed to load it
    if (fprintf(stdout, "Successfully loaded %s into trie in %f s.\n", dict, (double)(clock() - start) / CLOCKS_PER_SEC) < 0)
        print_perr();
}

/**
 * Loading the dictionnarys inside
 */
void construct_trie(Trie trie) {
    
    // loading : dictionnary
    fill_trie(trie, "dict/german-wordlist.txt", DE);
    fill_trie(trie, "dict/english-wordlist.txt", EN);
    fill_trie(trie, "dict/french-wordlist.txt", FR);
    
}

void construct_dawg(char* dict) {
    // Instantiate either a Trie or a DAWG here
    // ...

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE* fp;

    // open file 
    if ((fp = fopen(dict, "r")) == NULL)
        print_err("fopen construct_dawg");

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

    if(fclose(fp) != 0)
        print_err("fclose construct_dawg");
    free(line);

    // return ...;
}
