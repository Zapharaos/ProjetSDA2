#ifndef _LANG_H
#define _LANG_H

#define ALPHABET_SIZE 26

#include <stdbool.h>

typedef struct lang* Lang;

/** @struct lang
 *  @brief This structure creates a vertex for a node structure
 */
/** @var lang::fr
 *  Member 'fr' contains a boolean if french
 */
/** @var lang::de
 *  Member 'de' contains a boolean if german
 */
/** @var lang::en
 *  Member 'en' contains a boolean if english
 */
struct lang
{
    bool fr;
    bool de;
    bool en;
};

/** @enum language
 *  @brief This enum indicates a language
 */
/** @var language::UNKNOWN
 *  Member 'UNKNOWN' stands for an unknown language
 */
/** @var language::EN
 *  Member 'EN' stands for english
 */
/** @var language::FR
 *  Member 'FR' stands for french
 */
/** @var language::DE
 *  Member 'DE' stands for german
 */
enum language {
	UNKNOWN,
	EN,
	FR,
	DE
};

/**
 * @fn      Lang empty_lang()
 * @brief   Creates an empty lang structure
 * @return	an empty lang structure
 */
Lang empty_lang();

/**
 * @fn      void print_lang(Lang lang)
 * @brief   Displays the language
 * @param   lang lang to treat
 */
void print_lang(Lang lang);

/**
 * @fn      void word_lang(Lang lang)
 * @brief   Displays the language
 * @param   lang lang to treat
 */
void word_lang(Lang lang);

#endif
