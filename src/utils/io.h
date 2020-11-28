#ifndef _IO_H
#define _IO_H

#include "../data/trie.h"
#include "../data/dawg.h"

/**
 * @fn      fill_trie(Trie trie, char* dict, enum language lang)
 * @brief   Creates a trie structure and stores a dictionnary
 * @param   trie    the structure 
 * @param   dict    the path to the file 
 * @param   lang    the language
 * @pre     @p dict a dictionnary must exist at the path
 * @pre     @p lang must not be UNKNOWN
 */
void fill_trie(Trie trie, char* dict, enum language lang);

/**
 * @fn      construct_trie(Trie trie)
 * @brief   Loading the dictionnaries inside a trie
 * @param   trie    the trie where to store
 */
void construct_trie(Trie trie);

/**
 * @fn      construct_dawg(char* dict)
 * @brief   Creates a dawg structure and stores a dictionnary
 * @param   dict    the path to the file 
 * @return  the dawg structure
 * @pre     @p dict a dictionnary must exist at the path
 */
Dawg construct_dawg(char* dict);

/**
 * @fn      handle_args(int argc, char* argv[])
 * @brief   Starts the program depending on the list of arguments
 * @param   argv list of arguments
 * @return  0 if it succeded, 1 if it failed
 */
int handle_args(char* argv[]);

#endif
