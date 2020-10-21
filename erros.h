#ifndef _ERRORS_H
#define _ERRORS_H

#include <stdio.h>
#include <stdlib.h>

/**
 * \fn      void err_print()
 * \brief   Erreur avec la fonction bibliothèque fprintf
 */
void err_print();

 /**
  * \fn      void pas_content(char *message)
  * \brief   Erreur avec une fonction bibliothèque
  * \param   message Le message à afficher
  */
void pas_content(char *message);

#endif
