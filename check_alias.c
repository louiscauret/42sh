/*
** check_alias.c for 42sh in /home/hoarau_s/42SH/42-shell/Stephen/alias
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Thu May  3 11:33:29 2012 stephen hoarau
** Last update Sun May 20 15:50:35 2012 luc terracher
*/

#include "42.h"

void		check_alias(char *cmd, t_alias *alias, t_alias *alias_tmp)
{
  char		**tbl;
  t_alias	*head;

  head = alias;
  if ((tbl = my_str_to_wordtab(cmd, ' ')) == NULL)
    return ;
  while (head != NULL)
    {
      if (strcmp(tbl[1], head->memo) == 0)
	printf("%s='%s'\n", head->memo, head->cmd);
      head = head->next;
    }
  head = alias_tmp;
  while (head != NULL)
    {
      if (strcmp(tbl[1], head->memo) == 0)
	printf("%s=%s\n", head->memo, head->cmd);
      head = head->next;
    }
}
