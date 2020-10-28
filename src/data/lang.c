#include "lang.h"
#include <stdlib.h>
#include "../utils/errors.h"
#include <stdio.h>

Lang empty_lang()
{
	Lang lang = malloc(sizeof(Lang));
	lang->fr = false;
	lang->de = false;
	lang->en = false;
	return lang;
}

void print_lang(Lang lang)
{

	if (fprintf(stdout, "fr: %s | de: %s | en: %s\n", lang->fr ? "yes" : "no", lang->de ? "yes" : "no", lang->en ? "yes" : "no") < 0)
		print_perr();

}

void word_lang(Lang lang)
{
    
    if (fprintf(stdout, "%s %s %s\n", lang->fr ? "français" : "", lang->de ? "allemand" : "", lang->en ? "anglais" : "") < 0)
        print_perr();

}
