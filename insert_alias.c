/*
** insert_alias.c for 42sh in /home/hoarau_s/42SH/42-shell/Rendu
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Tue May 15 15:15:26 2012 stephen hoarau
** Last update Thu May 24 16:10:08 2012 stephen hoarau
*/

#include "42.h"

char		*insert_alias_tmp(char *command)
{
  t_alias	*l_alias;
  t_alias	*head;
  int		count;

  count = 0;
  l_alias = alias(NULL, 1, NULL);
  head = l_alias;
  while (l_alias != NULL)
    {
      count++;
      l_alias = l_alias->next;
    }
  l_alias = head;
  command = get_alias(l_alias, head, command, count);
  return (command);
}

char		*insert_alias_conf(char *command, int fd)
{
  t_alias	*l_alias;
  t_alias	*head;
  int		count;

  count = 0;
  l_alias = NULL;
  init_alias(&l_alias, fd);
  head = l_alias;
  while (l_alias != NULL)
    {
      count++;
      l_alias = l_alias->next;
    }
  command = get_alias(l_alias, head, command, count);
  return (command);
}
