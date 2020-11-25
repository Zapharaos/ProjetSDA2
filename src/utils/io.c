#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "utils.h"
#include "errors.h"
#include "test.h"
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
    if (fprintf(stdout, "Successfully loaded %s into dawg in %f s.\n", dict, (double)(clock() - start) / CLOCKS_PER_SEC) < 0)
        raler("fprintf in construct_dawg");

    return dawg;
}

/**
 * Starts the program depending of the number and list of arguments
 */
int handle_args(char* argv[])
{

    // if : help
    if (strcmp(argv[1], "-help") == 0)
    {
	    print_msg("--------------------- Language detector help ---------------------");
        print_msg("- Type <make list> to check out the list of possibilities");
	    print_msg("- Start : ./bin/ald -sentence <-trie,-dawg>");
        print_msg("\t Also : <make trie> or <make dawg>");
        print_msg("- Run the test : ./bin/ald -test");
        print_msg("\t Also : <make test>");
        print_msg("- Run the perf test for insert : ./bin/ald -insert <-trie,-dawg>");
        print_msg("\t Also : <make insert>");
        print_msg("- Run the perf test for search : ./bin/ald -search <-trie,-dawg>");
        print_msg("\t Also : <make search>");
        print_msg("------------------------------------------------------------------");

        // return : success
		exit(0);
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
            exit(0);
        }

        // if : dawg
        if (strcmp(argv[2], "-dawg") == 0)
        {
            
            print_msg("\nYou chose : Dawg \n");

            Dawg en = construct_dawg("dict/english-wordlist.txt");
            Dawg de = construct_dawg("dict/german-wordlist.txt");
            Dawg fr = construct_dawg("dict/french-wordlist.txt");

            start_dawg(en, de, fr);

            free_dawg(en);
            free_dawg(de);
            free_dawg(fr);

            // return success
            exit(0);
        }

        // else : failed
    	print_error("Arguments not found: type ./bin/ald -help to display help");
		exit(1);
    }

    // if : test
	if (strcmp(argv[1], "-test") == 0)
    {
        print_msg("\nYou chose : Test \n");

        // Trie
        test_trie("test/english-wordlist.txt", EN);
        test_trie("test/german-wordlist.txt", DE);
        test_trie("test/french-wordlist.txt", FR);

        // Dawg
        test_dawg("test/english-wordlist.txt");
        test_dawg("test/german-wordlist.txt");
        test_dawg("test/french-wordlist.txt");

        // return success
        exit(0);
    }

     // if : perf
	if (strcmp(argv[1], "-perf") == 0)
    {
        
        // if : trie
	    if (strcmp(argv[2], "-trie") == 0)
        {

            print_msg("\nInsert in Trie \n");

            time_insert("dict/english-wordlist.txt", "time/insert/trie-en.txt", EN, 0);
            time_insert("dict/german-wordlist.txt", "time/insert/trie-de.txt", DE, 0);
            time_insert("dict/french-wordlist.txt", "time/insert/trie-fr.txt", FR, 0);

            print_msg("\nSearch in Trie \n");

            time_search("dict/english-wordlist.txt", "time/search/trie-en.txt", EN, 0);
            time_search("dict/german-wordlist.txt", "time/search/trie-de.txt", DE, 0);
            time_search("dict/french-wordlist.txt", "time/search/trie-fr.txt", FR, 0);

            // return : success
            exit(0);
        }

        // if : dawg
        if (strcmp(argv[2], "-dawg") == 0)
        {
            
            print_msg("\nInsert in Dawg \n");

            time_insert("dict/english-wordlist.txt", "time/insert/dawg-en.txt", EN, 1);
            time_insert("dict/german-wordlist.txt", "time/insert/dawg-de.txt", DE, 1);
            time_insert("dict/french-wordlist.txt", "time/insert/dawg-fr.txt", FR, 1);

            print_msg("\nSearch in Dawg \n");

            time_search("dict/english-wordlist.txt", "time/search/dawg-en.txt", EN, 1);
            time_search("dict/german-wordlist.txt", "time/search/dawg-de.txt", DE, 1);
            time_search("dict/french-wordlist.txt", "time/search/dawg-fr.txt", FR, 1);


            // return success
            exit(0);
        }

        // else : failed
    	print_error("Arguments not found: type ./bin/ald -help to display help");
		exit(1);
    }
	
    // else : failed
	print_error("Arguments not found: type ./bin/ald -help to display help");
    exit(1);
}