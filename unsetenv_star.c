/*
** unsetenv_star.c for 42sh in /home/hoarau_s/42SH/42-shell/Rendu
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Sat May 19 14:51:25 2012 stephen hoarau
** Last update Sun May 20 15:45:58 2012 stephen hoarau
*/

#include "42.h"

int		unsetenv_star(char *cmd)
{
  int		i;

  i = 0;
  if (!cmd && !cmd[0])
    return (0);
  while (cmd[i])
    {
      if (cmd[i] == '*' && (cmd[i + 1] == ' ' || cmd[i + 1] == '\0'))
	return (1);
      ++i;
    }
  return (0);
}
