#include "lang.h"
#include <stdlib.h>
#include "../utils/errors.h"
#include <stdio.h>

/**
 * Creates an empty lang structure
 */
Lang empty_lang()
{
	// allocate memory for the structure
	Lang lang = malloc(sizeof(Lang));

	// if : malloc failed
	if(lang == NULL)
		raler("malloc empty_lang");

	// init elements
	lang->fr = false;
	lang->de = false;
	lang->en = false;
	
	// returns the lang
	return lang;
}

/**
 * Displays the language
 */
void print_lang(Lang lang)
{
	if (fprintf(stdout, "fr: %s | de: %s | en: %s\n", lang->fr ? "yes" : "no", lang->de ? "yes" : "no", lang->en ? "yes" : "no") < 0)
		raler("fprintf print_lang");
}

/**
 * Displays the language
 */
void word_lang(Lang lang)
{
    if (fprintf(stdout, "%s %s %s\n", lang->fr ? "french" : "", lang->de ? "german" : "", lang->en ? "english" : "") < 0)
        raler("fprintf word_lang");
}
