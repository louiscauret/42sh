/*
** add_space.c for 42sh in /home/hoarau_s/42SH/42-shell/Rendu
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Fri May 18 17:45:02 2012 stephen hoarau
** Last update Sun May 20 15:36:16 2012 luc terracher
*/

#include "42.h"

int		check_space(char *cmd, int i)
{
  if ((cmd[i] == '>' || cmd[i] == '<'))
    if (cmd[i + 1] != ' ' && cmd[i + 1] != '>' && cmd[i + 1] != '<')
      return (1);
  if ((cmd[i] != ' ' && cmd[i] != '>' && cmd[i] != '<'))
    if (cmd[i + 1] == '>' || cmd[i + 1] == '<')
      return (1);
  return (0);
}

int		check_opt(char *cmd, int i)
{
  if ((cmd[i] != ' ' && cmd[i + 1] == '>' && cmd[i + 2] != '>')
      || (i >= 2 && cmd[i] != ' ' && cmd[i - 1] == '>' && cmd[i - 2] != '>')
      || (cmd[i] != ' ' && cmd[i + 1] == '<' && cmd[i + 2] != '<')
      || (i >= 2 && cmd[i] != ' ' && cmd[i - 1] == '<' && cmd[i - 2] != '<')
      || (i >= 1 && cmd[i] == '>' && cmd[i + 1] == '>' && cmd[i - 1] != ' ')
      || (i >= 1 && cmd[i] == '>' && cmd[i - 1] == '>' && cmd[i + 1] != ' ')
      || (i >= 1 && cmd[i] == '<' && cmd[i + 1] == '<' && cmd[i - 1] != ' ')
      || (i >= 1 && cmd[i] == '<' && cmd[i - 1] == '<' && cmd[i - 1] != ' ')
      || (i == 0 && cmd[i] == '>' && cmd[i + 1] != ' ' && cmd[i + 1] != '>')
      || (i == 0 && cmd[i] == '<' && cmd[i + 1] != ' ' && cmd[i + 1] != '<'))
    return (1);
  return (0);
}

char		*modif_cmd(char *cmd, char *new)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (cmd[i])
    {
      if (check_space(cmd, i))
	{
	  new[j++] = cmd[i];
	  new[j] = ' ';
	}
      else
	new[j] = cmd[i];
      i++;
      j++;
    }
  return (new);
}

char		*add_space(char *cmd)
{
  int		i;
  int		space_needed;
  char		*new;

  i = 0;
  space_needed = 0;
  if (!cmd && !cmd[0])
    return (NULL);
  while (cmd[i])
    {
      if (check_opt(cmd, i))
	++space_needed;
      ++i;
    }
  if (space_needed == 0)
    return (cmd);
  if ((new = fmalloc((i + space_needed + 1) * sizeof(char *))) == NULL)
    return (NULL);
  new = modif_cmd(cmd, new);
  return (new);
}
