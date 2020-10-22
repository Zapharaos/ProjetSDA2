#include "errors.c"
#include "utils.c"
#include "trie.c"

int main(int argc, char* argv[]) {
    
    if(argc != 1) {}
    
    size_t n = 0; // number of words
    char** sentence = get_sentence(&n);
    
    free(sentence);
    
    return 0;
}
// --help
