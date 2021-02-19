/*
** my_clearscreen.c for my_clear_screen in /home/delbos_d//Library/Libtermcap
** 
** Made by damien delbos
** Login   <delbos_d@epitech.net>
** 
** Started on  Tue Jan 17 21:45:42 2012 damien delbos
** Last update Sun May 20 15:57:37 2012 louis cauret
*/

#include "42.h"

int	my_clear_screen(char *term)
{
  char	bp;
  int	ret;
  char	*area;

  if ((ret = tgetent(&bp, term)) == 0 || ret == -1)
    {
      if (ret == 0)
        my_error(M_ERRNAME, 1);
      else
        my_error(M_ERRDTB, 1);
      return (FAIL);
    }
  if ((area = tgetstr("cl", NULL)) == NULL)
    {
      my_error(M_ERRTGSRT, 1);
      return (FAIL);
    }
  tputs(area, 1, &my_putchar_int);
  if ((area = tgetstr("cl", NULL)) == NULL)
    {
      my_error(M_ERRTGSRT, 1);
      return (FAIL);
    }
  tputs(area, 1, &my_putchar_int);
  return (OK);
}
