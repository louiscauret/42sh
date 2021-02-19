/*
** get_alias_temp.c for 42sh in /home/hoarau_s/42SH/42-shell/Stephen/alias
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Thu May 10 15:30:56 2012 stephen hoarau
** Last update Sun May 20 16:10:14 2012 luc terracher
*/

#include "42.h"

char		*get_alias_temp(char *cmd, char **env)
{
  t_alias	*alias_tmp;
  t_alias	*tmp;

  alias_tmp = alias(cmd, 1, NULL);
  if (alias_tmp == NULL)
    return (NULL);
  tmp = alias_tmp;
  while (tmp != NULL)
    {
      if (strcmp(cmd, tmp->memo) == 0)
	return (clean_alias(tmp->cmd));
      tmp = tmp->next;
    }
  return ("OK");
}
