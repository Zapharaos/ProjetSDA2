#ifndef _IO_H
#define _IO_H
#include "../data/trie.h"
#include "../data/dawg.h"

/**
 * \fn      void fill_trie(Trie trie, char* dict, enum language lang)
 * \brief   Creates a structure and stores a dictionnary
 * \param   trie    the structure 
 * \param   dict    the path to the file 
 * \param   lang    the language
 */
void fill_trie(Trie trie, char* dict, enum language lang);

/**
 * Loading the dictionnarys inside
 */
void construct_trie(Trie trie);

Dawg construct_dawg(char* dict);

#endif
