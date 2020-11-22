#include <string.h>
#include <stdio.h>
#include "utils/errors.h"
#include "utils/utils.h"
#include "data/trie.h"
#include "utils/io.h"
#include "data/dawg.h"

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

int main(int argc, char* argv[])
{

    // if : too few arguments
	if (argc == 1)
    {
        print_error("Too few arguments: type ./bin/ald -help to display help");
        exit(1);
    }

    // if : too mich arguments
	if (argc > 3)
    {
        print_error("Too much arguments: type ./bin/ald -help to display help");
        exit(1);
    }

    // if : checking the arguments
    if(handle_args(argc, argv) == 0)
    {
        // return : program success
        return 0;
    }

    // return : program failed
    print_error("Arguments not found: type ./bin/ald -help to display help");
    exit(1);
}
