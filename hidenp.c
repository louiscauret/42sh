/*
** hidenp.c for hidenp in /home/hoarau_s/minishell2-2016-hoarau_s/lib/my
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Sun Mar  4 18:19:03 2012 stephen hoarau
** Last update Thu May  3 08:45:17 2012 luc terracher
*/

#include "42.h"

int		hidenp(char *s1, char *s2)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (s2[j] && s1[i])
    {
      if (s1[i] == s2[j])
	i++;
      j++;
    }
  if (!s1[i])
    return (0);
  return (1);
}
