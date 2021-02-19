/*
** match.c for auto_comp in /home/hoarau_s/42SH/autocompletion
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Wed Apr  4 22:45:53 2012 stephen hoarau
** Last update Sun May 20 16:25:31 2012 louis cauret
*/

#include "42.h"

int		get_slash(char *str)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (str[i] == '/')
	return (0);
      i++;
    }
  return (1);
}

char		**clean_tab(char **match)
{
  int		nbr;
  int		j;
  int		i;

  i = 0;
  while (match[i])
    {
      j = 0;
      while (match[i][j])
	{
	  if (match[i][j] == '/' && match[i][j + 1] != '\0')
	    nbr = j;
	  j++;
	}
      match[i] += nbr + 1;
      i++;
    }
   return (match);
}

void		clean_tilde(char **tbl, char *home)
{
  int		i;

  i = 0;
  while (tbl[i])
    {
      if (!strncmp(tbl[i], home, strlen(home) - 1))
	tbl[i] += strlen(home) - 2;
      tbl[i][0] = '~';
      i++;
    }
}

char		**manage_tilde(char *line, char **envp)
{
  glob_t	path;
  char		*tilde;

  if ((tilde = my_concat(get_env(envp, "HOME"), line + 2)) == NULL)
    return (NULL);
  if ((tilde = my_concat(tilde, "*")) == NULL)
    return (NULL);
  if ((glob(tilde, GLOB_MARK, NULL, &path)) == GLOB_NOMATCH)
    return (NULL);
  clean_tilde(path.gl_pathv, get_env(envp, "HOME"));
  clean_tab(path.gl_pathv);
  return (path.gl_pathv);
}

char		**get_matches(char *dir, char *line, char **envp)
{
  char		*tmp;
  int		ret;
  glob_t	path;

  if (dir == NULL)
    return (NULL);
  if (line[0] != '~')
    {
      if (!(tmp = my_concat(dir, line)) || !(tmp = my_concat(tmp, "*")))
	return (NULL);
    }
  else
    return (manage_tilde(line, envp));
  ret = glob(tmp, GLOB_MARK, NULL, &path);
  if (ret == GLOB_NOMATCH || ret == GLOB_ABORTED || ret == GLOB_NOSPACE)
    return (NULL);
  clean_tab(path.gl_pathv);
  return (path.gl_pathv);
}
