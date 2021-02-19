/*
** get_nbr_words.c for 42sh in /home/hoarau_s/42SH/42-shell/Stephen/alias
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Thu May  3 05:52:26 2012 stephen hoarau
** Last update Sun May 20 16:11:44 2012 luc terracher
*/

#include "42.h"

int		get_nbr_words(char **command)
{
  int		i;

  i = 0;
  while (command[i])
    i++;
  return (i);
}
