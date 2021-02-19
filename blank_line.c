/*
** blank_line.c for autocomp in /home/hoarau_s/42SH/autocompletion
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Wed Apr  4 21:16:20 2012 stephen hoarau
** Last update Sun May 20 15:48:17 2012 luc terracher
*/

#include "42.h"

int		blank_line(char **envp)
{
  char		*ls[3];
  pid_t		pid;

  if ((pid = xfork()) == -1)
    return (FAIL);
  if (pid == 0)
    {
      if (!(ls[0] = xstrdup("/bin/ls")))
	return (FAIL);
      ls[1] = NULL;
      ls[2] = NULL;
      if ((execve(ls[0], ls, envp)) == -1)
	if (my_write(1, "\n", 1) == -1)
	  return (FAIL);
    }
  else
    wait(0);
  return (OK);
}
