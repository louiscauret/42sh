/*
** add_alias.c for add_alias in /home/terrac_l//42-shell/Rendu
**
** Made by luc terracher
** Login   <terrac_l@epitech.net>
**
** Started on  Sun May 20 15:33:27 2012 luc terracher
** Last update Sun May 20 15:33:51 2012 luc terracher
*/

#include "42.h"

int		erase_alias(t_alias *tmp_alias, char *memo, char *cmd)
{
  t_alias	*head;

  head = tmp_alias;
  while (head != NULL)
    {
      if (!strcmp(head->memo, memo))
	{
	  head->cmd = cmd;
	  return (0);
	}
      head = head->next;
    }
  return (1);
}

char		*add_alias(char *cmd, t_alias **alias_tmp)
{
  char		**tbl;
  t_alias	*alias_cur;

  cmd += 6;
  alias_cur = alias(NULL, 1, NULL);
  if ((tbl = my_str_to_wordtab(cmd, '=')) == NULL)
      return (NULL);
  if (tbl[1] == NULL)
    my_put_in_list(alias_tmp, tbl[0], "\0");
  else
    {
      if (tbl[1][0] != '\'' && tbl[1][strlen(tbl[1]) - 1] != '\'')
	{
	  printf("Alias must be declared like : alias key='word'. ");
	  printf("Set as empty by default\n.");
	  if (erase_alias(*alias_tmp, tbl[0], clean_alias(tbl[1])))
	    my_put_in_list(alias_tmp, tbl[0], clean_alias(tbl[1]));
	  return ("");
	}
      if (erase_alias(*alias_tmp, tbl[0], clean_alias(tbl[1])))
	my_put_in_list(alias_tmp, tbl[0], clean_alias(tbl[1]));
    }
  return ("");
}
