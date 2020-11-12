#include <string.h>
#include <stdio.h>
#include "utils/errors.h"
#include "utils/utils.h"
#include "data/trie.h"
#include "utils/io.h"

int handle_args(int argc, char* argv[])
{
    // if : too few arguments
    // return : failed
	if (argc <= 1)
		return 1;

    // if : help
    if (strcmp(argv[1], "-help") == 0)
    {
	    print_msg("------------ Language detector help ------------");
        print_msg("Tips: type <make install> to use <ald> instead of <./ald>");
	    print_msg("Get sentence: ./ald -sentence <-trie,-dawg>");
	    print_msg("Test trie data structure: ./ald -trie");

        // return : success
		return 0;
    }

    // if : sentence
	if (strcmp(argv[1], "-sentence") == 0)
    {
        
        // if : trie
	    if (strcmp(argv[2], "-trie") == 0)
        {

            print_msg("\nYou chose : Trie \n");

            // init : new structure Trie
            Trie trie = empty_trie();

            // loading the dictionnarys inside the Trie structure
            fill_trie(trie, "dict/german-wordlist.txt", DE);
            fill_trie(trie, "dict/english-wordlist.txt", EN);
            fill_trie(trie, "dict/french-wordlist.txt", FR);

            // start : program
            start_trie(trie);

            // free : structure
    	    free_trie(trie);

            // return : success
            return 0;
        }

        // if : dawg
        if (strcmp(argv[2], "-dawg") == 0)
        {
            //todo :

            // return success
            return 0;
        }

        // return : failed
		return 1;
    }
	
    // else : failed
	print_err("Argument not found: type ./ald -help to display help");

    // return : failed
    return 1;
}

int main(int argc, char* argv[]) {

    // if : checking the arguments
    if(handle_args(argc, argv) == 0)
    {
        // return : program success
        return 0;
    }

    // return : program failed
    print_err("Options not found: type ./ald -help to display help");
    return 1;
}
