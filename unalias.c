/*
** unalias.c for 42.h in /home/hoarau_s/42SH/42-shell/Stephen/alias
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Mon May 14 04:46:43 2012 stephen hoarau
** Last update Sun May 20 15:55:13 2012 stephen hoarau
*/

#include	"42.h"

void		match_alias(t_alias **tmp_alias, char *cmd)
{
  t_alias	*head;

  head = *tmp_alias;
  while (*tmp_alias != NULL)
    {
      if (!strcmp((*tmp_alias)->memo, cmd))
	{
	  if ((*tmp_alias)->prev == NULL)
	    head = (*tmp_alias)->next;
	  else
	    (*tmp_alias)->prev->next = (*tmp_alias)->next;
	}
      *tmp_alias = (*tmp_alias)->next;
    }
  *tmp_alias = head;
}

int		unalias(char *cmd, t_alias **tmp_alias, t_minish *min)
{
  char		**tbl;
  int		i;

  cmd += 8;
  if (((tbl = my_str_to_wordtab(cmd, ' ')) == NULL) || (tmp_alias == NULL))
    {
      fprintf(stderr, "unalias: Not enought arguments.\n");
      return (1);
    }
  i = 0;
  while (tbl[i])
    match_alias(tmp_alias, tbl[i++]);
  min->exec_cmd = OK;
  return (0);
}
