#ifndef _IO_H
#define _IO_H
#include "../data/trie.h"
#include "../data/dawg.h"

/**
 * \fn      void fill_trie(Trie trie, char* dict, enum language lang)
 * \brief   Creates a trie structure and stores a dictionnary
 * \param   trie    the structure 
 * \param   dict    the path to the file 
 * \param   lang    the language
 */
void fill_trie(Trie trie, char* dict, enum language lang);

/**
 * \fn      construct_trie(Trie trie)
 * \brief   Loading the dictionnarys inside a trie
 * \param   trie    the trie where to store
 */
void construct_trie(Trie trie);

/**
 * \fn      construct_dawg(char* dict)
 * \brief   Creates a dawg structure and stores a dictionnary
 * \param   dict    the path to the file 
 * \return  the dawg structure
 */
Dawg construct_dawg(char* dict);

#endif
