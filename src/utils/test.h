#include "../data/lang.h"

#define EN_NB_WORDS 370103
#define FR_NB_WORDS 336528
#define DE_NB_WORDS 685620
#define MIN_WORDS_DICT 327700

/**
 * @fn      test_trie(char* path, enum language lang)
 * @brief   Creates a trie from a file and search from the same file
 * @param   path the path of the file
 * @param   lang the language of the trie
 */
void test_trie(char* path, enum language lang);

/**
 * @fn      test_dawg(char* path)
 * @brief   Creates a dawg from a file and search from the same file
 * @param   path the path of the file
 */
void test_dawg(char* path);

/**
 * @fn      time_insert(char* dict, char* file, enum language lang, int boolean)
 * @brief   Times the time needed in order to insert words in a given language and mode
 * @param   dict the path to the dictionnary file
 * @param   file the path to file where to store the time
 * @param   lang the language of the dictionnary and the words
 * @param   boolean 0 if trie, 1 if dawg
 */
void time_insert(char* dict, char* file, enum language lang, int boolean);

/**
 * @fn      time_search(char* dict, char* file, enum language lang, int boolean)
 * @brief   Times the time needed in order to search for words in a given language and mode
 * @param   dict the path to the dictionnary file
 * @param   file the path to file where to store the time
 * @param   lang the language of the dictionnary and the words
 * @param   boolean 0 if trie, 1 if dawg
 */
void time_search(char* dict, char* file, enum language lang, int boolean);