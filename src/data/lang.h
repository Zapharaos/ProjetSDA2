#ifndef _LANG_H
#define _LANG_H

#define ALPHABET_SIZE 26

#include <stdbool.h>

typedef struct lang* Lang;

struct lang
{
    bool fr;
    bool de;
    bool en;
};

enum language {
	UNKNOWN,
	EN,
	FR,
	DE
};

Lang empty_lang();

void print_lang(Lang lang);

void word_lang(Lang lang)

#endif
