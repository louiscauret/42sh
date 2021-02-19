/*
** my_kill_keyboard.c for my_kill_keyboard in /home/delbos_d//Library/Libtermcap
** 
** Made by damien delbos
** Login   <delbos_d@epitech.net>
** 
** Started on  Tue Jan 17 22:13:59 2012 damien delbos
** Last update Sun May 20 16:12:03 2012 louis cauret
*/

#include "42.h"

int			recover_struct_term(struct termios *t)
{
  if (tcgetattr(0, t) == -1)
    return (FAIL);
  return (OK);
}

int			my_kill_keyboard(int opt, struct termios t_prev)
{
  struct termios	t;

  if (recover_struct_term(&t) == FAIL)
    return (OK);
  if (opt)
    {
      t.c_lflag &= ~ECHO;
      t.c_lflag &= ~ICANON;
      t.c_cc[VMIN] = 1;
      t.c_cc[VTIME] = 0;
    }
  else
    t = t_prev;
  if (tcsetattr(0, 1, &t) == -1)
    {
      my_error(M_TCSATTR, 1);
      return (FAIL);
    }
  return (OK);
}
