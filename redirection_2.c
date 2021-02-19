/*
** redirection_2.c for redirection_2.c in /home/delbos_d//Projets/42-SH/Rendu
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Thu May 17 17:34:29 2012 damien delbos
** Last update Sun May 20 15:36:25 2012 stephen hoarau
*/

#include "42.h"

static char	**cpy_char(char **cmd, int i)
{
  while (cmd[i])
    {
      cmd[i] = cmd[i + 1];
      i++;
    }
  return (cmd);
}

char		*recover_match(t_minish *min, int i, char *match)
{
  char		c;

  if (min->tmp[i + 1] && min->tmp[i + 1][0] != '<' &&
      min->tmp[i + 1][0] != '>' &&  min->tmp[i + 1][0] != '|')
    match = min->tmp[i + 1];
  if (i == 0)
    {
      ++(min->tmp);
      ++(min->tmp);
    }
  else
    {
      min->tmp = cpy_char(min->tmp, i);
      if (!min->tmp[i])
	return (NULL);
      c = min->tmp[i][0];
      if (c != '<' && c != '>' && c != '|')
	{
	  min->tmp = cpy_char(min->tmp, i);
	}
    }
  return (match);
}

void		cut_redir(t_minish *min, char *redir)
{
  int		e;
  int		s;

  s = 0;
  while (min->cmd[s] && strncmp(&(min->cmd[s]), redir, strlen(redir)))
    s++;
  e = s;
  while (min->cmd[e] == *redir)
    e++;
  while (min->cmd[e] == ' ')
    e++;
  while (min->cmd[e] && min->cmd[e] != ' ' && min->cmd[e] != '\t')
    e++;
  strcpy(&(min->cmd[s]), &(min->cmd[e]));
  min->cmd = clean_str(min->cmd);
}
