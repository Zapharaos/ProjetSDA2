#ifndef _TRIE_H
#define _TRIE_H

#include <stdlib.h>
#include "lang.h"

typedef struct trie* Trie;

/** @struct trie
 *  @brief This structure creates a dictionnary
 */
/** @var trie::data
 *  Member 'data' contains the next node
 */
/** @var trie::lang
 *  Member 'lang' contains the node's language
 */
struct trie
{
    Trie data[ALPHABET_SIZE];
    Lang lang;
};

/**
 * @fn      Trie empty_trie()
 * @brief   Creates an empty Trie structure
 * @return  Trie structure
 */
Trie empty_trie();

/**
 * @fn      void free_trie(Trie trie)
 * @brief   Free a Trie structure
 * @param   trie trie to free
 */
void free_trie(Trie trie);

/**
 * @fn      void display_trie(Trie trie)
 * @brief   Displays a Trie structure
 * @param   trie trie to display
 */
void display_trie(Trie trie);

/**
 * @fn      void insert_trie(Trie trie, const char* word, enum language lang, size_t index)
 * @brief   Inserts a word inside a Trie structure
 * @param   trie trie where to insert
 * @param   word word to insert
 * @param   lang the language of the word
 * @param   index iterator
 */
void insert_trie(Trie trie, const char* word, enum language lang, size_t index);

/**
 * @fn      Lang search_trie(Trie trie, const char* word, size_t index)
 * @brief   Searchs the language of a word
 * @param   trie trie where to search
 * @param   word word to search
 * @param   index iterator
 * @return  lang of the word
 */
Lang search_trie(Trie trie, const char* word, size_t index);

/**
 * @fn      void count_trie(Trie trie, char** sentence, const size_t n, int count[])
 * @brief   Count how many times a language is used inside a sentence
 * @param   trie trie where to search
 * @param   sentence the sentence to treat
 * @param   n the size of the sentence
 * @param   count array storing the iteratos
 */
void count_trie(Trie trie, char** sentence, const size_t n, int count[]);

/**
 * @fn      void treat_trie(Trie trie, char** sentence, size_t n)
 * @brief   Treats a sentence
 * @param   trie trie to treat
 * @param   sentence the sentence to treat
 * @param   n the size of the sentence
 */
void treat_trie(Trie trie, char** sentence, size_t n);

/**
 * @fn      void start_trie(Trie trie)
 * @brief   start the langue detector using the Trie structure
 * @param   trie    the structure
 */
void start_trie(Trie trie);

/**
 * @fn      void search_trie_from_file(Trie trie, char* path)
 * @brief   searchs all words from a file inside a trie
 * @param   trie dawg to treat
 * @param   path file to read from
 */
void search_trie_from_file(Trie trie, char* path);

size_t count(Trie trie);

#endif // !_TRIE_H
