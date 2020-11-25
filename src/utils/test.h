#include "../data/lang.h"

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