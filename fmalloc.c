/*
** fmalloc.c for fmalloc in /home/delbos_d//Projets/42-SH/svn_42sh
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Mon Apr 16 09:50:49 2012 damien delbos
** Last update Thu May  3 08:46:47 2012 luc terracher
*/

#include "42.h"

void	*fmalloc(int size)
{
  void	*res;
  int	i;
  char	*str;

  i = 0;
  if ((res = malloc(size)) == NULL)
    {
      if (write(2, ERR_MALLOC, strlen(ERR_MALLOC)) == -1)
	return (NULL);
      return (NULL);
    }
  str = res;
  while (i < size)
    str[i++] = 0;
  return (str);
}
