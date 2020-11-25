#include "../data/lang.h"

#define EN_NB_WORDS 370103
#define FR_NB_WORDS 336528
#define DE_NB_WORDS 685620

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

void time_insert(char* dict, char* file, enum language lang, int boolean);

void time_search(char* dict, char* file, enum language lang, int boolean);