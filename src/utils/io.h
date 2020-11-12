#ifndef _IO_H
#define _IO_H
#include "../data/trie.h"

/**
 * \fn      void fill_trie(Trie trie, char* dict, enum language lang)
 * \brief   Creates a structure and stores a dictionnary
 * \param   trie    the structure 
 * \param   dict    the path to the file 
 * \param   lang    the language
 */
void fill_trie(Trie trie, char* dict, enum language lang);

/**
 * \fn      display_trie(Trie trie)
 * \brief   Search for the most occurred language in a sentence
 * \param   trie    the structure
 * \param   sentence the sentence to treat
 * \param   n    the number of words in the sentence
 */
void start_trie(Trie trie);

void construct_dawg(char* dict);

#endif
