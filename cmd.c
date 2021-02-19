/*
** cmd.c for autocomplet in /home/hoarau_s/42SH/autocompletion
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Thu Apr  5 03:48:51 2012 stephen hoarau
** Last update Wed May 23 19:19:57 2012 damien delbos
*/

#include "42.h"

char		*get_files(char **tbl, char *line)
{
  glob_t	path;
  int		i;

  i = 1;
  glob(tbl[0], GLOB_MARK, NULL, &path);
  while (tbl[i])
    glob(tbl[i++], GLOB_MARK | GLOB_APPEND, NULL, &path);
  if (path.gl_pathv == NULL)
    return (line);
  clean_tab(path.gl_pathv);
  my_sort_tab(path.gl_pathv);
  if (path.gl_pathv && path.gl_pathv[0] && !path.gl_pathv[1])
    return (path.gl_pathv[0]);
  else
    display_double_tab(path.gl_pathv);
  return (line);
}

char		*cmds(char *line, char **envp)
{
  char		**tbl;
  int		i;

  i = 0;
  if (!(tbl = my_str_to_wordtab(get_env(envp, "PATH"), ':')))
    return (NULL);
  while (tbl[i])
    {
      if (tbl[i][strlen(tbl[i]) - 1] == '/')
	{
	  if (!(tbl[i] = my_concat(tbl[i], my_concat(line, "*"))))
	    return (NULL);
	}
      else if (tbl[i][strlen(tbl[i]) - 1] != '/')
	{
	  if (!(tbl[i] = my_concat(tbl[i], my_concat("/", line))) ||
	      !(tbl[i] = my_concat(tbl[i], "*")))
	    return (NULL);
	}
      i++;
    }
  return (get_files(tbl, line));
}
