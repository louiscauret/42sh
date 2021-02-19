/*
** alias.c for 42sh in /home/hoarau_s/42SH/42-shell/Stephen/alias
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Thu May  3 04:32:21 2012 stephen hoarau
** Last update Thu May 24 16:15:23 2012 stephen hoarau
*/

#include "42.h"

char		*clean_alias(char *alias)
{
  int		len;

  if (alias[0] == '\'')
    alias = alias + 1;
  len = strlen(alias);
  if (alias[len - 1] == '\'')
    alias[len - 1] = '\0';
  return (alias);
}

char		**modif_tab(char **command, int pos, char *alias)
{
  command[pos] = xstrdup(alias);
  return (command);
}

char		*concat_tab(char **tbl)
{
  char		*line;
  int		i;

  i = 1;
  if (!tbl[0])
    return ("");
  line = xstrdup(tbl[0]);
  if (line == NULL)
    return ("");
  while (tbl[i])
    {
      if (!(line = my_concat(line, " ")))
	return (NULL);
      if (!(line = my_concat(line, tbl[i])))
	return (NULL);
      i++;
    }
  return (line);
}

char		*get_alias(t_alias *alias, t_alias *head,
			   char *command, int len)
{
  char		**tbl;
  int		idx_line;
  t_alias	*tmp;

  idx_line = 0;
  head = head;
  while (len != 0)
    {
      if ((tbl = my_str_to_wordtab(command, ' ')) == NULL)
	return (command);
      tmp = cpy_alias(alias);
      while (tmp != NULL)
	{
	  idx_line = 0;
	  while (tbl[idx_line])
	    if (!strcmp(tmp->memo, tbl[idx_line++]))
	      {
		tbl = modif_tab(tbl, idx_line - 1, clean_alias(tmp->cmd));
		tmp->memo = "USED";
	      }
	  command = concat_tab(tbl);
	  tmp = tmp->next;
	}
      len--;
    }
  return (command);
}

char		*manage_alias(char *command, char **env)
{
  int		fd;

  if ((env == NULL) || (env[0] == NULL) ||
      (!strncmp(command, "alias", 5)) || (!strncmp(command, "unalias", 7)))
    return (command);
  if ((fd = xopen_conf(env)) == -1)
    return (command);
  command = insert_alias_tmp(command);
  if (command == NULL)
      return (NULL);
  command = insert_alias_conf(command, fd);
  if (close(fd) == -1)
    return (NULL);
  return (command);
}
