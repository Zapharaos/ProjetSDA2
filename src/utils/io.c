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
 * Search for the most occurred language in a sentence
 */
void start_trie(Trie trie) {

    // init : sentence entered by user
    size_t n = 0;
	char** sentence = get_sentence(&n);

	// count : how many words per language in the sentence
	int count[3] = {0,0,0};
	count_lang_trie(trie, sentence, n, count);
	
	// print : how many words per language + detection result
	char* result = sentence_lang(count);
	fprintf(stdout,"\n%d word(s) in french.\n", count[0]);
	fprintf(stdout,"%d word(s) in german.\n", count[1]);
	fprintf(stdout,"%d word(s) in english.\n", count[2]);
	fprintf(stdout,"\nMain language is : %s.\n", result);

    // free : sentence
    free_sentence(sentence);

    print_msg("\nType y to restart (anything else will end the programm) :");

    if (getchar() == 'y') {

        // issue : in fgets due to \n character after using getchar
        int c;
        while ( (c = getchar()) != EOF && c != '\n') {}

        // start : re starting
        print_msg("\nStarting again...");
        start_trie(trie);
    }
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
