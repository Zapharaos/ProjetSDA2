#ifndef _UTILS_H
#define _UTILS_H

#include <stdlib.h>
#include <string.h> // strtok_r()
#include <stddef.h>

#define NB_WORD_MAX 64
#define SENTENCE_MAX_SIZE 256

void to_lower(char* entry);

/**
 * \fn      char** get_sentence(size_t* n)
 * \brief   Retourne un tableau 2D de la phrase
 * \param   *n Le nombre de mots dans la phrase
 */
char** get_sentence(size_t* n);

#endif
