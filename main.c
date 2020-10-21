#include "errors.c"
#include "utils.c"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    
    if(argc != 1) {}
    
    size_t n = 0; // number of words
    char** sentence = get_sentence(&n);
    
    for(size_t i=0; i<n; i++)
        if(fprintf(stdout, "%s\n", sentence[i]) < 0)
            err_print();
    
    free(sentence);
    
    return 0;
}
// --help
