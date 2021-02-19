/*
** auto_completion.c for auto_completion in /home/delbos_d//Projets/42-SH/svn_42sh/Stephen/autocompletion
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Fri Apr 27 17:15:14 2012 damien delbos
** Last update Thu May 17 17:09:57 2012 stephen hoarau
*/

#include "42.h"

static char	*last_space(char *line)
{
  int		i;
  char		**tbl;

  i = 0;
  if (!(tbl = my_str_to_wordtab(line, ' ')))
    return (NULL);
  while (tbl[i])
    i++;
  if (tbl[i - 1][0] == '\0')
    return ("*");
  return (tbl[i - 1]);
}

static char	*concat_path(char *occ, char *last_word)
{
  int		i;
  int		nb;
  char		*new_occ;

  i = 0;
  nb = 0;
  while (last_word[i])
    {
      if (last_word[i] == '/')
	nb = i;
      i++;
    }
  new_occ = strndup(last_word, nb);
  if (!(new_occ = my_concat(new_occ, "/")))
    return (NULL);
  if (!(new_occ = my_concat(new_occ, occ)))
    return (NULL);
  return (new_occ);
}

static char	*concat_line(char **tbl, char *occ)
{
  int		i;
  char		*line;

  i = 1;
  if (!tbl[1] && tbl[0][0] == '.' && tbl[0][1] == '/')
    return (my_concat("./", occ));
  else if (!tbl[1] && tbl[0][0] == '/')
    return (get_absolute(tbl[0], occ));
  if (!(line = my_concat(tbl[0], " ")))
    return (NULL);
  while (tbl[i])
    {
      if (tbl[i + 1] != NULL)
	if (!(line = my_concat(line, tbl[i])) || !(line = my_concat(line, " ")))
	  return (NULL);
      i++;
    }
  if (tbl[i] == NULL && ((tbl[i - 1][0] == '.' && tbl[i - 1][1] == '.')
			 || (tbl[i - 1][0] == '/')
			 || ((get_slash(tbl[i - 1]) == 0))))
    if (!(occ = concat_path(occ, tbl[i - 1])))
      return (NULL);
  line = my_concat(line, occ);
  return (line);
}

static char	*manage_cmd(char **match, char *line, char *lin,
			    char **envp)
{
  char		**tbl;

  if (!(tbl = my_str_to_wordtab(lin, ' ')))
    return (NULL);
  if ((strcmp(tbl[0], line) == 0))
    return (cmds(line, envp));
  else if (match == NULL)
    return (lin);
  else if (match[1] == NULL)
    return (concat_line(tbl, match[0]));
  else
    display_double_tab(match);
  return (lin);
}

char		*auto_complete(char *lin, char **envp, char **match, char *line)
{
  char		*tmp[2];
  char		*path;

  if (lin[0] == '\0')
    {
      if (blank_line(envp) == FAIL)
	return (NULL);
    }
  else
    {
      if (!(line = last_space(lin)) || !(path = get_env(envp, "PWD")))
	return (NULL);
      if (!(tmp[0] = xstrdup(path)) || !(tmp[1] = xstrdup(line)) ||
	  manage_path(tmp) == FAIL)
	  return (NULL);
      if (tmp[0][strlen(tmp[0]) - 1] != '/')
	path = strcpy(path, tmp[0]);
      match = get_matches(my_concat(path, "/"), tmp[1], envp);
      return (manage_cmd(match, tmp[1], lin, envp));
    }
  return ("");
}
