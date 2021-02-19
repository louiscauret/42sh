/*
** xfork.c for xfork in /home/hoarau_s/Documents/Minishell2/lib/my
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Sun Mar  4 10:06:35 2012 stephen hoarau
** Last update Sun May 20 16:00:23 2012 stephen hoarau
*/

#include "42.h"

int		xfork()
{
  int		pid;

  if ((pid = fork()) == -1)
    my_error(ERR_FORK, 1);
  return (pid);
}
