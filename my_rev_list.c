/*
** my_rev_list.c for rev_list in /home/hoarau_s/tmp/corewar-2016-gaube_j/asm_d/src
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Thu May 10 14:16:28 2012 stephen hoarau
** Last update Sun May 20 16:14:27 2012 louis cauret
*/

#include "42.h"

void		my_rev_list(t_alias **begin)
{
  t_alias	*previous;
  t_alias	*save;
  t_alias	*list;

  list = *begin;
  previous = NULL;
  save = list;
  while (save != NULL)
    {
      save = list->next;
      list->next = previous;
      previous = list;
      list = save;
    }
  *begin = previous;
}
