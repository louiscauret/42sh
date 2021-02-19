/*
** tools.c<2> for tools in /home/delbos_d//Projets/MiniShell_2
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Wed Dec 14 23:38:05 2011 damien delbos
** Last update Sun May 20 15:53:50 2012 stephen hoarau
*/

#include "42.h"

void		my_free_tblstr(char **str)
{
  int		i;

  i = 0;
  while (str && str[i])
    free(str[i++]);
}

void		my_free_minishell(t_minish *min)
{
  int		i;

  i = 0;
  if (min->path)
    while (min->path[i])
      free(min->path[i++]);
}

int		my_strlen_cd(char *str)
{
  int		i;

  i = 0;
  while (str[i] && str[i] != '/')
    i++;
  return (i);
}

char		*xstrdup(char *str)
{
  char		*cpy;

  if (!(cpy = strdup(str)))
    my_error(ERR_STDUP, 1);
  return (cpy);
}

int		count_par(char *str)
{
  int		guill;
  int		cot;
  int		i;

  i = 0;
  guill = 0;
  cot = 0;
  while (str[i])
    {
      if (str[i] == '"')
        ++guill;
      if (str[i] == '\'')
        ++cot;
      ++i;
    }
  if ((cot % 2) != 0 || (guill % 2) != 0)
    return (0);
  return (1);
}
