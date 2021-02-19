/*
** my_cursor_move.c for my_cursor_move in /home/delbos_d//Library/Libtermcap
** 
** Made by damien delbos
** Login   <delbos_d@epitech.net>
** 
** Started on  Tue Jan 17 21:59:37 2012 damien delbos
** Last update Sun May 20 15:59:17 2012 louis cauret
*/

#include "42.h"

int	my_cursor_move(int x, int y, char *term)
{
  char	bp;
  char	*area;
  char	*move;
  int	ret;

  if ((ret = tgetent(&bp, term)) == 0 || ret == -1)
    {
      my_error(M_ERRTGENT, 1);
      return (FAIL);
    }
  if ((area = tgetstr("cm", NULL)) == NULL)
    {
      my_error(M_ERRTGSRT, 1);
      return (FAIL);
    }
  if ((move = tgoto(area, x, y)) == NULL)
    {
      my_error(M_ERRTGSRT, 1);
      return (FAIL);
    }
  tputs(move, 1, &my_putchar_int);
  return (OK);
}
