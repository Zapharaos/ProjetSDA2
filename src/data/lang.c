#include "lang.h"
#include <stdlib.h>
#include "../utils/errors.h"
#include <stdio.h>

Lang empty_lang()
{
	Lang lang = malloc(sizeof(Lang));

	if(lang == NULL)
		raler("malloc empty_lang");

	lang->fr = false;
	lang->de = false;
	lang->en = false;
	
	return lang;
}

void print_lang(Lang lang)
{
	if (fprintf(stdout, "fr: %s | de: %s | en: %s\n", lang->fr ? "yes" : "no", lang->de ? "yes" : "no", lang->en ? "yes" : "no") < 0)
		raler("fprintf print_lang");
}

void word_lang(Lang lang)
{
    if (fprintf(stdout, "%s %s %s\n", lang->fr ? "french" : "", lang->de ? "german" : "", lang->en ? "english" : "") < 0)
        raler("fprintf word_lang");
}
