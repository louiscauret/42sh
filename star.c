/*
** star.c for star in /home/serra_r//42-shell/test
**
** Made by romain serra
** Login   <serra_r@epitech.net>
**
** Started on  Wed May  2 11:47:25 2012 romain serra
** Last update Sun May 20 15:50:49 2012 stephen hoarau
*/

#include <glob.h>
#include "42.h"

static int	my_size_glob(char **parse)
{
  int		i;
  int		cmpt;

  i = 0;
  cmpt = -1;
  while (parse[i] != NULL)
    cmpt += strlen(parse[i++]) + 1;
  return (cmpt);
}

static int	manag_error_star(char **cmd, glob_t **path, char **tmp)
{
  int		ret;

  if (!(*path = fmalloc(sizeof(**path))))
    return (-1);
  ret = glob(*cmd, GLOB_MARK, NULL, *path);
  if (ret == GLOB_ABORTED || ret == GLOB_NOSPACE)
    return (-1);
  if (ret == GLOB_NOMATCH)
    return (2);
  if (!(*tmp = fmalloc(sizeof(char) * my_size_glob((*path)->gl_pathv))))
    return (-1);
  return (1);
}

static char	*replace_star_tab(char *cmd)
{
  glob_t	*path;
  char		*tmp;
  int		i;
  int		j;
  int		ret;

  if ((ret = manag_error_star(&cmd, &path, &tmp)) == -1)
    return (NULL);
  if (ret == 2)
    return (cmd);
  j = 0;
  i = -1;
  tmp[0] = '\0';
  while (path->gl_pathv[++i])
    {
      if (i)
	tmp[j++] = ' ';
      strcpy(&tmp[j], path->gl_pathv[i]);
      j += strlen(path->gl_pathv[i]);
    }
  free(cmd);
  cmd = tmp;
  globfree(path);
  return (cmd);
}

static char	**save_star(char **cmd_tab)
{
  int		i;

  i = -1;
  while (cmd_tab[++i])
    {
      if (strchr(cmd_tab[i], '*'))
	{
	  if ((i >= 1 && !strcmp(cmd_tab[i - 1], "unsetenv"))
	      || (i >= 1 && (cmd_tab[i - 1][0] == '<')))
	    return (cmd_tab);
	  else if (!(cmd_tab[i] = replace_star_tab(cmd_tab[i])))
	    return (NULL);
	}
    }
  return (cmd_tab);
}

char		*manag_star(char *cmd)
{
  char		**cmd_tab;
  int		i;
  int		nb;

  i = -1;
  if (!cmd)
    return (NULL);
  if (!*cmd)
    return (cmd);
  if (!(cmd_tab = my_str_to_wordtab(cmd, ' ')))
    return (NULL);
  if (!(cmd_tab = save_star(cmd_tab)))
    return (NULL);
  if (!(cmd = fmalloc(my_size_glob(cmd_tab) + 2)))
    return (NULL);
  while (cmd_tab[++i])
    {
      nb = strlen(cmd_tab[i]) + strlen(cmd);
      strcat(&cmd[strlen(cmd)], cmd_tab[i]);
      cmd[nb] = ' ';
      cmd[nb + 1] = 0;
      free(cmd_tab[i]);
    }
  cmd[strlen(cmd) - 1] = 0;
  return (cmd);
}
