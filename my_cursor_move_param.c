/*
** my_cursor_move_param.c for my_cursor_move_param in /home/delbos_d//Library/Libtermcap
** 
** Made by damien delbos
** Login   <delbos_d@epitech.net>
** 
** Started on  Thu Apr  5 00:47:27 2012 damien delbos
** Last update Sun May 20 16:00:10 2012 louis cauret
*/

#include "42.h"

int	my_cursor_move_param(char *term, char *atri)
{
  char	bp;
  char	*area;
  int	ret;

  if ((ret = tgetent(&bp, term)) == 0 || ret == -1)
    {
      my_error(M_ERRTGENT, 1);
      return (FAIL);
    }
  if ((area = tgetstr(atri, NULL)) == NULL)
    {
      my_error(M_ERRTGSRT, 1);
      return (FAIL);
    }
  tputs(area, 1, &my_putchar_int);
  return (OK);
}
