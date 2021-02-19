/*
** cpy_alias.c for cpy_alias in /home/hoarau_s/42sh-2016-delbos_d
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Thu May 24 15:56:27 2012 stephen hoarau
** Last update Thu May 24 16:13:35 2012 stephen hoarau
*/

#include "42.h"

t_alias			*cpy_alias(t_alias *alias)
{
  t_alias		*cpy;
  t_alias		*init;

  if (!alias)
    return (NULL);
  init = alias;
  cpy = NULL;
  while (alias != NULL)
    {
      my_put_in_list(&cpy, alias->memo, alias->cmd);
      alias = alias->next;
    }
  my_rev_list(&cpy);
  alias = init;
  return (cpy);
}
