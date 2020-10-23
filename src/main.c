#include <string.h>
#include <stdio.h>
#include "utils/errors.h"
#include "utils/utils.h"

int main(int argc, char* argv[]) {
    
    if(argc > 1)
    {

    	if(strcmp(argv[1], "-help") == 0)
    	{
            print_msg("------------ Language detector help ------------");
            print_msg("Get sentence: ./lg -sentence");
            print_msg("Test trie data structure: ./lg -trie");
    	}
    	else if (strcmp(argv[1], "-sentence") == 0)
    	{
            size_t n = 0; // number of words
            char** sentence = get_sentence(&n);
            free(sentence);

    	}
    	else if(strcmp(argv[1], "-trie") == 0)
    	{
    		
    	}
    	else
    	{
            print_err("Argument not found: type ./lg -help to display help");
    	}
    	
    } else
    {
        print_err("Option not found: type ./lg -help to display help");
    }

    return 0;
}
// --help
