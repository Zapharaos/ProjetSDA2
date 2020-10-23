#ifndef _ERRORS_H
#define _ERRORS_H

/**
 * \fn      void print_perr()
 * \brief   Erreur avec la fonction bibliothèque fprintf
 */
void print_perr();

 /**
  * \fn      void print_err(char *message)
  * \brief   Erreur avec une fonction bibliothèque
  * \param   message Le message à afficher
  */
void print_err(char *message);

void print_msg(char* message);

#endif
