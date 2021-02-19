/*
** list.c for linked list example in /home/hoarau_s//Documents/Jour_12
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Tue Oct 25 09:26:50 2011 stephen hoarau
** Last update Wed May 23 16:07:39 2012 stephen hoarau
*/

#include "42.h"

t_alias		*my_put_in_list(t_alias **list, char *memo, char *cmd)
{
  t_alias	*element;

  element = fmalloc(sizeof(*element));
  if (element == NULL)
    return (NULL);
  element->memo = memo;
  element->cmd = cmd;
  element->next = *list;
  element->prev = NULL;
  if (*list != NULL)
    (*list)->prev = element;
  *list = element;
  return (0);
}
