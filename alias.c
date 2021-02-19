/*
** alias.c for 42sh in /home/hoarau_s/42SH/42-shell/Stephen/alias
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Thu May  3 11:12:28 2012 stephen hoarau
** Last update Sun May 20 16:31:54 2012 stephen hoarau
*/

#include "42.h"

static void		display_alias(t_alias *alias, t_alias *alias_tmp)
{
  my_show_list(&alias);
  my_show_list(&alias_tmp);
  return;
}

static int		manage_declaration(char *cmd)
{
  int			idx;

  idx = 0;
  while (cmd[idx])
    {
      if (cmd[idx] == '=')
	return (0);
      idx++;
    }
  return (1);
}

void			init_alias(t_alias **alias, int fd)
{
  char			**tbl;
  char			*buffer;

  *alias = NULL;
  while ((buffer = get_next_line(fd)) != NULL)
      {
	if (buffer[0] != '#' && buffer[0] != '\0')
	  {
	    if (check_line_conf(buffer))
	      {
		tbl = epur_alias(buffer + 6);
		my_put_in_list(alias, tbl[0], tbl[1]);
		free(buffer);
	      }
	}
      }
  my_rev_list(alias);
}

static char		*usage_alias(char *cmd, t_alias **alias_tmp,
				     char **env, int idx)
{
  static int		bol;
  static t_alias	*list_alias;
  char			**tbl;
  int			fd;

  if ((tbl = my_str_to_wordtab(cmd, ' ')) == NULL)
    return (NULL);
  if ((fd = xopen_conf(env)) == -1)
    return ("");
  if (bol == 0)
    {
      init_alias(&list_alias, fd);
      bol = 1;
    }
  while (tbl[idx])
    idx++;
  if (idx == 1)
    display_alias(list_alias, *alias_tmp);
  else if (idx != 1 && (manage_declaration(cmd)) == 0)
    return (add_alias(cmd, alias_tmp));
  else
    check_alias(cmd, list_alias, *alias_tmp);
  if (close(fd) == -1)
    return (NULL);
  return ("");
}

t_alias			*alias(char *cmd, int opt, t_minish *min)
{
  static t_alias	*alias_tmp = NULL;

  if (opt == 1)
    return (alias_tmp);
  else if (opt == 2)
    {
      if (unalias(cmd, &alias_tmp, min) == 1)
	{
	  min->exit = 1;
	  return (NULL);
	}
    }
  else if (usage_alias(cmd, &alias_tmp, min->env, 0) == NULL)
    {
      min->exit = 1;
      return (NULL);
    }
  return (NULL);
}
