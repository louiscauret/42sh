/*
** my_execve.c for 42sh in /home/hoarau_s/42SH/42-shell/Rendu
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Sat May 19 16:01:11 2012 stephen hoarau
** Last update Sun May 20 16:07:33 2012 louis cauret
*/

#include "42.h"

void		manage_ret_access(t_minish *min, int *bol)
{
  if (!access(min->cmd, F_OK))
    {
      *bol = 1;
      if (!access(min->cmd, R_OK | W_OK))
	*bol = 2;
      else
	execve(min->cmd, min->tmp, min->env);
    }
}

int		test_exec(t_minish *min)
{
  int		i;
  int		bol;

  i = 0;
  bol = 0;
  while (min->path[i])
    {
      if (!(min->cmd = creat_way(min->path[i++], min->tmp[0])))
	return (FAIL);
      manage_ret_access(min, &bol);
    }
  if (bol == 1 || bol == 2)
    return (FAIL);
   return (OK);
}

int		my_execve(t_minish *min)
{
  int		i;
  int		bol;

  i = 0;
  bol = 0;
  execve(min->tmp[0], min->tmp, min->env);
  while (min->path[i])
    {
      if (!(min->cmd = creat_way(min->path[i++], min->tmp[0])))
	return (FAIL);
      manage_ret_access(min, &bol);
    }
  if (bol == 0)
    if (fprintf(stderr, "%s: Command not found\n", min->tmp[0]) < 0)
      return (FAIL);
  if (bol == 1)
    if (fprintf(stderr, "%s: Permission denied\n", min->tmp[0]) < 0)
      return (FAIL);
  min->exec_cmd = FAIL;
  return (FAIL);
}
