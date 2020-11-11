#ifndef _ERRORS_H
#define _ERRORS_H

/**
 * \fn      void print_perr()
 * \brief   An error was encountered using frprintf
 * \return  1
 */
void print_perr();

 /**
  * \fn      void print_err(char *message)
  * \brief   An error was encountered
  * \param   message Message to display
  * \return  EXIT_FAILURE
  */
void print_err(char *message);

 /**
  * \fn      void print_msg(char* message)
  * \brief   Displays a message
  * \param   message Message to display
  */
void print_msg(char* message);

#endif
