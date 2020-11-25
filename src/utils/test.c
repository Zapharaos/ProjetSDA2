#include "test.h"
#include "utils.h"
#include "errors.h"
#include "io.h"
#include "../data/trie.h"
#include "../data/dawg.h"

void test_trie(char* path, enum language lang)
{
    // init : trie 
    Trie trie = empty_trie();
    fill_trie(trie, path, lang);
    
    // init : sentence from file
    size_t n = 0;
    char** sentence = get_sentence_from_file(path, &n);

	// treat : sentence	
    treat_trie(trie, sentence, n);
    
    // free : sentence and trie
    free_sentence(sentence);
    free_trie(trie);
}

void test_dawg(char* path)
{
    // init : main dawg
    Dawg dawg = construct_dawg(path);

    // init : empty dawg
    Dawg empty = empty_dawg();

    // init : sentence from file
    size_t n = 0;
    char** sentence = get_sentence_from_file(path, &n);

	// treat : sentence	
    treat_dawg(dawg, empty, empty, sentence, n);

	// free : sentence and dawg
    free_sentence(sentence);
    free_dawg(empty);
    free_dawg(dawg);
}