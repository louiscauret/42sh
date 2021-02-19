/*
** pipe.c for pipe in /home/delbos_d//Projets/MiniShell_2
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Thu Mar  1 10:42:05 2012 damien delbos
** Last update Sun May 20 16:01:02 2012 damien delbos
*/

#include "42.h"

int		test_pipe(char *cmd)
{
  char		**pip;
  int		i;
  char		*cpy;

  i = 0;
  if (!(pip = separate_cmd(cmd, '|')))
    return (-1);
  while (pip[i])
    {
      cpy = epur_str(pip[i]);
      if (!cpy[0])
	{
	  if (my_error(ERR_VOID_CMD, 1) == -1)
	    return (-1);
	  return (0);
	}
      ++i;
    }
  my_free_tblstr(pip);
  return (1);
}

static int	manag_fils(t_minish *min, int j, t_pipe *my_pip, int i)
{
  if (j > 1)
    if (!(my_pip->fd = manag_pipe(min, j - 1)))
      return (FAIL);
  min->cmd = epur_str(min->str_bet_pip[j - 1]);
  if (!(min->tmp = my_str_to_wordtab(min->cmd, ' ')))
    return (FAIL);
  i = 0;
  if (manag_redirection(min, &min->redir1, &min->redir2, 0) == FAIL ||
      min->exit)
    return (FAIL);
  if (!(*(min->cmd)) && my_error(ERR_VOID_CMD, 1))
    return (FAIL);
  if (my_close(my_pip->fd_2[0]) == -1 || my_dup2(my_pip->fd_2[1], 1) == -1)
    return (FAIL);
  execve(min->tmp[0], min->tmp, min->env);
  while (min->path[i])
    {
      if (!(min->cmd = creat_way(min->path[i++], min->tmp[0])))
	return (FAIL);
      execve(min->cmd, min->tmp, min->env);
    }
  my_error(epur_str(min->str_bet_pip[j - 1]), 1);
  my_error(ERR_CMD_NF, 1);
  my_pip->fd = NULL;
  return (FAIL);
}

static int	*manag_pere(t_minish *min, int j, t_pipe *my_pip, pid_t pid)
{
  int		status;

  waitpid(pid, &status, WNOHANG);
  if (j > 1 && my_pip->fd != NULL)
    {
      if (my_dup2(0, my_pip->fd[0]) == -1 || my_close(my_pip->fd[0]) == -1)
	return (NULL);
      free(my_pip->fd);
    }
  if (my_dup2(my_pip->fd_2[0], 0) == -1 || my_dup2(1, my_pip->fd_2[1]) == -1 ||
      my_close(my_pip->fd_2[1]) == -1)
    return (NULL);
  my_free_tblstr(min->tmp);
  return (my_pip->fd_2);
}

int		*manag_pipe(t_minish *min, int j)
{
  int		pid;
  t_pipe	my_pip;

  my_pip.redir1 = 0;
  my_pip.redir2 = 0;
  my_pip.fd = NULL;
  if (!(my_pip.fd_2 = fmalloc(sizeof(int) * 2)))
    return (NULL);
  if (my_pipe(my_pip.fd_2) == -1 || (pid = xfork()) == -1)
    return (NULL);
  if (pid == 0)
    {
      manag_fils(min, j, &my_pip, 0);
      return (NULL);
    }
  else
    return (manag_pere(min, j, &my_pip, pid));
  return (my_pip.fd_2);
}
