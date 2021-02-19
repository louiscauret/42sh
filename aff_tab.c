/*
** aff_tab.c for aff_tab in /home/hoarau_s/minishell1-2016-hoarau_s
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Thu Mar  1 14:45:47 2012 stephen hoarau
** Last update Sun May 20 15:37:46 2012 luc terracher
*/

#include "42.h"

void		display_double_tab(char **str)
{
  int		j;

  j = 0;
  while (str[j])
    printf("%s\n", str[j++]);
}
