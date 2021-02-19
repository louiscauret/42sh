/*
** my_concat.c for my_concat in /home/hoarau_s/cpe-rush2-2016-hoarau_s/lib/my
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Sat Feb 25 17:42:14 2012 stephen hoarau
** Last update Sat May  5 14:35:25 2012 damien delbos
*/

#include "42.h"

char		*my_concat(char *old, char *new)
{
  int		i;
  int		j;
  char		*new_str;

  i = 0;
  j = 0;
  if (!(new_str = fmalloc((strlen(old) + strlen(new) + 1) *
			  sizeof(*new_str))))
    return (NULL);
  while (old[i])
    {
      new_str[i] = old[i];
      i++;
    }
  while (new[j])
    new_str[i++] = new[j++];
  new_str[i] = '\0';
  return (new_str);
}
