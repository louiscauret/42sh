/*
** get_absolute.c for 42sh in /home/hoarau_s/42SH/42-shell/Rendu
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Tue May 15 13:28:28 2012 stephen hoarau
** Last update Sun May 20 16:08:20 2012 luc terracher
*/

#include "42.h"

char		*get_absolute(char *line, char *occ)
{
  int		idx;
  int		count;

  idx = 0;
  while (line[idx])
    {
      if (line[idx] == '/')
	count = idx;
      idx++;
    }
  line[++count] = '\0';
  if ((line = my_concat(line, occ)) == NULL)
    return (NULL);
  return (line);
}
