#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>

#define NB_WORD_MAX 700000
#define WORD_MAX_SIZE 64
#define SENTENCE_MAX_SIZE 256
#define max(a,b)            (((a) > (b)) ? (a) : (b))

/**
 * @fn      char** get_sentence(size_t* n)
 * @brief   Creates a sentence given by the user
 * @param   n pointer with the number of words inside a sentence
 * @return  Double char array with the sentence
 * @pre     @p n initializd at 0
 */
char** get_sentence(size_t* n);

/**
 * @fn      char** get_sentence_from_file(char* path, size_t* n)
 * @brief   Creates a sentence from a file
 * @param   path the path of the file
 * @param   n pointer with the number of words inside a sentence
 * @return  Double char array with the sentence
 * @pre     @p path path must exists
 * @pre     @p n initializd at 0
 */
char** get_sentence_from_file(char* path, size_t* n);

/**
 * @fn      void show_sentence(char** sentence, size_t n)
 * @brief   Displays every words inside a given sentence
 * @param   sentence the array containg a sentence
 * @param   n the number of words inside a sentence
*/
void show_sentence(char** sentence, size_t n);

/**
 * @fn      char** init_sentence(void)
 * @brief   Allocates memory to store a sentence
 * @return  Double char array
*/
char** init_sentence(void);

/**
 * @fn      void free_sentence(char** sentence)
 * @brief   Free memory allocated to a double char array
 * @param   sentence the array containg a sentence
*/
void free_sentence(char** sentence);

/**
 * @fn      char* get_random_line(char* path, size_t max)
 * @brief   Returns the word at a random line inside a file
 * @param   path the path to read from
 * @param   max the max index of a line
 * @returns a string at a random line
 * @pre     @p path path must exists
*/
char* get_random_line(char* path, size_t max);

/**
 * @fn      void to_lower(char* entry)
 * @brief   Transform every char in a string into lower cases
 * @param   entry the word to transform
*/
void to_lower(char* entry);

/**
 * @fn      size_t ascii_to_index(char c)
 * @brief   Change ASCII char (a-z) to array index
 * @param   c the char to treat
 * @return  the array index
*/
size_t ascii_to_index(char c);

/**
 * @fn      void remove_char(char* word, size_t index)
 * @brief   Remove char from a string at a given index
 * @param   word the string to edit
 * @param   index the index to remove
*/
void remove_char(char* word, size_t index);

/**
 * @fn      void parse_word(char* word)
 * @brief   Remove all char from given string that aren't a-z
 * @param   word the word to edit
*/
void parse_word(char* word);

/**
 * @fn      char* concat(const char* s1, const char* s2)
 * @brief   Concat two strings together
 * @param   s1 first string
 * @param   s2 second string
 * @return  both strings concatained
*/
char* concat(const char* s1, const char* s2);

/**
 * @fn      int max(int lang[])
 * @brief   search the biggest value in an array
 * @param   lang array to treat
 * @return  the biggest value
*/
int array_max(int lang[]);

/**
 * @fn      char* sentence_lang(int count[])
 * @brief   Gives the language that has the biggest iterator
 * @param   count array with the iterators
 * @return  the principal language
*/
char* sentence_lang(int count[]);

#endif
