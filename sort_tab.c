/*
** sort_list.c for myls in /home/hoarau_s//myls-2016-hoarau_s
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Sun Dec  4 15:54:17 2011 stephen hoarau
** Last update Thu May  3 08:48:24 2012 luc terracher
*/

#include "42.h"

char		**my_sort_tab(char **parse)
{
  int		i;
  int		j;
  int		change;
  char		*tmp;

  change = 1;
  j = 0;
  while (change != 0 && parse[i])
    {
      i = 0;
      change = 0;
      while (parse[i + 1] != NULL)
	{
	  if (strcmp(parse[i], parse[i + 1]) == 1)
	    {
	      tmp = parse[i];
	      parse[i] = parse[i + 1];
	      parse[i + 1] = tmp;
	      change++;
	    }
	  i++;
	  j++;
	}
    }
  return (parse);
}
