/*
** minishell_2.c for minishell_2 in /home/delbos_d//Projets/MiniShell_2
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Thu Feb 23 17:20:01 2012 damien delbos
** Last update Wed May 23 21:10:15 2012 damien delbos
*/

#include "42.h"

int		manag_builtin(t_minish *min)
{
  int		err;

  if (if_builtin(min->cmd, &err))
    {
      if (err || (manag_fonction(min) == OK && min->exit &&
                  (min->exec_cmd = FAIL) == FAIL))
        return (FAIL);
      return (FAIL);
    }
  return (OK);
}

static int	manag_fils(t_minish *min, int **fd, int *j, int i)
{
  if (!strncmp("/bin/kill", min->cmd, strlen("/bin/kill")) ||
      !strncmp("kill", min->cmd, strlen("kill")))
    if (setpgrp() == -1)
      return (FAIL);
  if (manag_redirection(min, &min->redir1, &min->redir2, 0) == FAIL)
    return (FAIL);
  if (min->exit || !(min->str_bet_pip = separate_cmd(min->cmd, '|')))
    return (FAIL);
  if ((*j = my_strlen_tbl(min->str_bet_pip)) == 0)
    *j = 1;
  if (*j > 1)
    if (!(*fd = manag_pipe(min, *j - 1)))
      return (FAIL);
  min->cmd = epur_str(min->str_bet_pip[*j - 1]);
  if (!(min->tmp = my_str_to_wordtab(min->cmd, ' ')))
    return (FAIL);
  min->exec_cmd = OK;
  if ((!(*(min->cmd)) && my_error(ERR_VOID_CMD, 1)) ||
      manag_builtin(min) == FAIL)
    return (FAIL);
  while (min->tmp[i])
    clean_quote_2(min->tmp[i++]);
  return (my_execve(min));
}

int		interpret_cmd(t_minish *min)
{
  int		pid;
  int		status;
  int		*fd;
  int		j;

  j = 0;
  if ((pid = xfork()) == -1)
    return (FAIL);
  if (pid == 0)
    return (manag_fils(min, &fd, &j, 0));
  wait(&status);
  min->exec_cmd = get_return_value(status);
  if (j > 1 && fd == NULL)
    return (OK);
  else if (j > 1)
    {
      if (my_dup2(0, fd[0]) == -1 || my_close(fd[0]) == -1)
	return (FAIL);
      free(fd);
    }
  my_free_tblstr(min->tmp);
  return (OK);
}

void		manag_slash(int slash, char *cmd, int j, char *dir)
{
  while (cmd[j])
    if (cmd[j++] == '/')
      slash++;
  j = 0;
  while (slash > 0 && *cmd)
    {
      if (*cmd == '/')
        slash--;
      dir[j++] = *cmd;
      cmd++;
    }
}

char		*creat_way(char *path_name, char *cmd)
{
  char		*res;

  if (!(res = fmalloc(strlen(path_name) + strlen(cmd) + 2)))
    return (NULL);
  res = strcpy(res, path_name);
  res[strlen(path_name)] = '/';
  strcpy(&res[strlen(res)], cmd);
  return (res);
}
