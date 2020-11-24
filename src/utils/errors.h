#ifndef _ERRORS_H
#define _ERRORS_H

/**
 * \fn      raler(char *message)
 * \brief   An error was encountered
 */
void raler(char *message);

 /**
  * \fn      print_error(char *message)
  * \brief   Displays a message in stderr
  * \param   message Message to display
  */
void print_error(char *message);

 /**
  * \fn      print_msg(char* message)
  * \brief   Displays a message in stdout
  * \param   message Message to display
  */
void print_msg(char* message);

#endif
