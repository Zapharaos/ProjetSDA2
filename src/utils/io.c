#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "utils.h"
#include "errors.h"
#include "../data/trie.h"
#include "../data/dawg.h"

/**
 * Creates a trie structure and stores a dictionnary
 */
void fill_trie(Trie trie, char* dict, enum language lang)
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE* fp;
    clock_t start = clock();

    // open : file given as paramater (i.e. a dictionnary)
    if ((fp = fopen(dict, "r")) == NULL)
        raler("fopen in fill_trie");

    // reset errno var at 0
    errno = 0;

    // read : file given as paramater (i.e. a dictionnary)
    while ((read = getline(&line, &len, fp)) != -1)
    {
        // remove newline
        size_t length = strlen(line);
        if ((length > 0) && (line[length - 1] == '\n'))
        {
            line[length - 1] = '\0';
        }

        // parsing the word
        parse_word(line);

        // insert : word inside the Trie structure given as paramater
        insert_trie(trie, line, lang, 0);

        // reset errno var at 0
        errno = 0;
    }

    // if : error using getline
    if(errno != 0)
        raler("getline in fill_trie");

    // free : line
    free(line);
    
    // close : file given as paramater (i.e. a dictionnary)
    if(fclose(fp) != 0)
        raler("fclose in fill_trie");

    // print : success + time needed to load it
    if (fprintf(stdout, "Successfully loaded %s into trie in %f s.\n", dict, (double)(clock() - start) / CLOCKS_PER_SEC) < 0)
        raler("fprintf in fill_trie");
}

/**
 * Loading the dictionnarys inside
 */
void construct_trie(Trie trie)
{
    // loading : dictionnary
    fill_trie(trie, "dict/german-wordlist.txt", DE);
    fill_trie(trie, "dict/english-wordlist.txt", EN);
    fill_trie(trie, "dict/french-wordlist.txt", FR);
}

/**
 * Creates a dawg structure and stores a dictionnary
 */
Dawg construct_dawg(char* dict)
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE* fp;
    clock_t start = clock();
    Dawg dawg = empty_dawg();

    // open : file given as paramater (i.e. a dictionnary)
    if ((fp = fopen(dict, "r")) == NULL)
        raler("fopen in construct_dawg");

    // reset errno var at 0
    errno = 0;

    // read : file given as paramater (i.e. a dictionnary)
    while ((read = getline(&line, &len, fp)) != -1)
    {
        // remove newline
        size_t length = strlen(line);
        if ((length > 0) && (line[length - 1] == '\n'))
        {
            line[length - 1] = '\0';
        }

        // parsing the word
        parse_word(line);

        // insert : word inside the Dawg structure given as paramater
        insert_dawg(dawg, line);

        // reset errno var at 0
        errno = 0;
    }
    
    // if : error using getline
    if(errno != 0)
        raler("getline in construct_dawg");

    // free : line
    free(line);

    // minimiser to depth 0
    minimize(dawg, 0);

    // close : file given as paramater (i.e. a dictionnary)
    if(fclose(fp) != 0)
        raler("fclose in construct_dawg");

    // print : success + time needed to load it
    if (fprintf(stdout, "Successfully loaded %s into dawg in %f s.\n", dict, (double)(clock() - start) / (double)CLOCKS_PER_SEC) < 0)
        raler("fprintf in construct_dawg");

    return dawg;
}

/**
 * Starts the program depending of the number and list of arguments
 */
int handle_args(int argc, char* argv[])
{

    // if : help
    if (strcmp(argv[1], "-help") == 0)
    {
	    print_msg("------------ Language detector help ------------");
        print_msg("Tips: type <make install> to use <ald> instead of <./ald>");
        print_msg("\t type <make list> to check out the list");
	    print_msg("Get a sentence: ./bin/ald -sentence <-trie,-dawg>");
        print_msg("------------------------------------------------");

        // return : success
		return 0;
    }

    if(strcmp(argv[1], "-test") == 0)
    {

        if(strcmp(argv[2], "-dawg") == 0)
        {
            Dawg fr = construct_dawg("dict/english-wordlist.txt");
            char* line = NULL;
            size_t len = 0;
            ssize_t read;
            FILE* fp;

            if ((fp = fopen("dict/english-wordlist.txt", "r")) == NULL)
                raler("fopen in construct_dawg");

            // reset errno var at 0
            errno = 0;

            FILE *fpe;

            fpe = fopen("listedpqsdplqspdo.txt", "w+");
         
            size_t words = 0;
            size_t found = 0;

            // read : file given as paramater (i.e. a dictionnary)
            while ((read = getline(&line, &len, fp)) != -1)
            {
                // remove newline
                size_t length = strlen(line);
                if ((length > 0) && (line[length - 1] == '\n'))
                {
                    line[length - 1] = '\0';
                }

                if(word_exists(fr->root, line, 0))
                {
                    found++;
                } else {
                    fprintf(fpe, "%s\n", line);
                }

                words++;

                // reset errno var at 0
                errno = 0;
            }

            fclose(fpe);

            
            // if : error using getline
            if(errno != 0)
                raler("getline in construct_dawg");

            // free : line
            free(line);

            // close : file given as paramater (i.e. a dictionnary)
            if(fclose(fp) != 0)
                raler("fclose in construct_dawg");

            printf("Word count : %ld, words found: %ld\n", words, found);

            /*

            printf("Est-ce que le mot carotte existe? %s\n", word_exists(fr->root, "carotte", 0) ? "Oui" : "Non");
            printf("Est-ce que le mot pain existe? %s\n", word_exists(fr->root, "pain", 0) ? "Oui" : "Non");
            printf("Est-ce que le mot monsieur existe? %s\n", word_exists(fr->root, "monsieur", 0) ? "Oui" : "Non");
            printf("Est-ce que le mot voiture existe? %s\n", word_exists(fr->root, "voiture", 0) ? "Oui" : "Non");
            printf("Est-ce que le mot tracteur existe? %s\n", word_exists(fr->root, "tracteur", 0) ? "Oui" : "Non");
            printf("Est-ce que le mot esperluette existe? %s\n", word_exists(fr->root, "esperluette", 0) ? "Oui" : "Non");
            
            char words[10][16] = {
                "a",
                "abaissa",
                "abaissable",
                "abaissables",
                "abaissai",
                "abaissaient"
                ,
                "abaissais",
                "abaissait",
                "abaissames",
                "abaissant"
            };

            // char words[3][16] = {
            //     "ion",
            //     "lotion",
            //     "lotte"
            // }; 

            for (size_t i = 0; i < 10; i++)
            {
                printf("Est-ce que le mot %s existe? %s\n", words[i], word_exists(fr->root,  words[i], 0) ? "Oui" : "Non");
            }
            */

          //  display_node(fr->root);

            free_dawg(fr);

            return 0;
        }

        return 1;
    }

    // if : sentence
	if (strcmp(argv[1], "-sentence") == 0)
    {

        // if : trie
	    if (strcmp(argv[2], "-trie") == 0)
        {

            print_msg("\nYou chose : Trie \n");

            Trie trie = empty_trie();
            construct_trie(trie);
            start_trie(trie);
    	    free_trie(trie);

            // return : success
            return 0;
        }

        // if : dawg
        if (strcmp(argv[2], "-dawg") == 0)
        {
            //todo :
            print_msg("\nYou chose : Dawg \n");

            Dawg en = construct_dawg("dict/english-wordlist.txt");
            Dawg de = construct_dawg("dict/german-wordlist.txt");
            Dawg fr = construct_dawg("dict/french-wordlist.txt");

            start_dawg(en, de, fr);
        
            free_dawg(en);
            free_dawg(de);
            free_dawg(fr);

            // return success
            return 0;
        }

        // else : failed
    	//print_error("Arguments not found: type ./bin/ald -help to display help");
		return 1;
    }
	
    // else : failed
	//print_error("Arguments not found: type ./bin/ald -help to display help");
    return 1;
}