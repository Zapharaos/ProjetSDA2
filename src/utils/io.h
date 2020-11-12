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
 * \fn      start_trie(Trie trie)
 * \brief   start the langue detector using the Trie structure
 * \param   trie    the structure
 */
void start_trie(Trie trie);

void construct_dawg(char* dict);

#endif
