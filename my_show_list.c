/*
** my_show_list.c for pushswap in /home/hoarau_s//Documents/Pushswap
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Tue Jan  3 03:38:30 2012 stephen hoarau
** Last update Sun May 20 15:49:27 2012 damien delbos
*/

#include "42.h"

void		my_show_list(t_alias **list)
{
  t_alias	*tmp;

  tmp = *list;
  while (tmp != NULL)
    {
      if (printf("%s='%s'\n", tmp->memo, tmp->cmd) < 0)
	return ;
      tmp = tmp->next;
    }
}
