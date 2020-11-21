#ifndef _TRIE_H
#define _TRIE_H

#include <stdlib.h>
#include "lang.h"

typedef struct trie* Trie;

/**
 * \struct  trie
 * \brief   Creates a dictionnary
 */
struct trie
{
    Trie* data;
    Lang lang;
};

/**
 * \fn      empty_trie()
 * \brief   Creates an empty Trie structure
 * \return  Trie structure
 */
Trie empty_trie();

/**
 * \fn      free_trie(Trie trie)
 * \brief   Free a Trie structure
 * \param   trie trie to free
 */
void free_trie(Trie trie);

/**
 * \fn      display_trie(Trie trie)
 * \brief   Displays a Trie structure
 * \param   trie trie to display
 */
void display_trie(Trie trie);

/**
 * \fn      insert_trie(Trie trie, const char* word, enum language lang, size_t index)
 * \brief   Inserts a word inside a Trie structure
 * \param   trie trie where to insert
 * \param   word word to insert
 * \param   lang the language of the word
 * \param   index iterator
 */
void insert_trie(Trie trie, const char* word, enum language lang, size_t index);

/**
 * \fn      search_trie(Trie trie, const char* word, size_t index)
 * \brief   Searchs the language of a word
 * \param   trie trie where to search
 * \param   word word to search
 * \param   index iterator
 * \return  lang of the word
 */
Lang search_trie(Trie trie, const char* word, size_t index);

/**
 * \fn      search_trie(Trie trie, const char* word, size_t index)
 * \brief   Count how many times a language is used inside a sentence
 * \param   trie trie where to search
 * \param   sentence the sentence to treat
 * \param   n the size of the sentence
 * \param   count array storing the iteratos
 */
void count_trie(Trie trie, char** sentence, const size_t n, int count[]);

/**
 * \fn      start_trie(Trie trie)
 * \brief   start the langue detector using the Trie structure
 * \param   trie    the structure
 */
void start_trie(Trie trie);

#endif // !_TRIE_H
