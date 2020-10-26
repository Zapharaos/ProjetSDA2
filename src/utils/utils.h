#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>

#define NB_WORD_MAX 64
#define SENTENCE_MAX_SIZE 256

/**
 * \fn      void to_lower(char* entry)
 * \brief   Transforme une chaine de caractère en minuscule
 * \param   entry La chaîne de caractère à modifier
*/
void to_lower(char* entry);

/**
 * \fn      char** get_sentence(size_t* n)
 * \brief   Retourne un tableau double pointeur de la phrase
 * \param   n Le nombre de mots dans la phrase
 */
char** get_sentence(size_t* n);

/**
 * \fn      void show_sentence(char** sentence, size_t* n)
 * \brief   Affiche les mots de la phrase stockée dans le tableau
 * \param   sentence Le tableau contenant les mots de la phrase
 * \param   n Le nombre de mots dans la phrase
*/
void show_sentence(char** sentence, size_t* n);

size_t ascii_to_index(char c);

void remove_char(char* word, size_t index);

void parse_word(char* word);

char* concat(const char* s1, const char* s2);

int max(int lang[]);

void print_result(char result, int count[]);

#endif
