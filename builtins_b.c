/*
** builtins_b.c for builtins_b in /home/delbos_d//Projets/42-SH/svn_42sh/Rattrapage
** 
** Made by damien delbos
** Login   <delbos_d@epitech.net>
** 
** Started on  Wed May 23 20:53:40 2012 damien delbos
** Last update Wed May 23 20:54:17 2012 damien delbos
*/

#include "42.h"

static void	do_others(t_minish *min)
{
  if (!strncmp(min->cmd, "cd", 2))
    min->env = my_cd(&min->cmd[2], min->env, min);
  else if (!strncmp(min->cmd, "echo", strlen("echo")))
    my_echo(&min->cmd[strlen("echo")], min);
  else if (!strncmp(min->cmd, "alias", strlen("alias")))
    alias(min->cmd, 0, min);
  else if (!strncmp(min->cmd, "unalias", strlen("unalias")))
    alias(min->cmd, 2, min);
}

int		manag_fonction(t_minish *min)
{
  min->exit = 0;
  if ((manag_redirection(min, &(min->redir1), &(min->redir2), 0) == FAIL &&
      (min->exit = 1)) || (min->exit && !(min->exit = 0)))
    return (OK);
  if (!strncmp(min->cmd, "exit", 4) || !strcmp(min->cmd, ""))
    {
      if (strcmp(min->cmd, "exit") != 0)
	min->nb_exit = atoi(min->cmd + 5);
      min->exit = 1;
    }
  else if (!strncmp(min->cmd, "env", 3) &&
	   my_env(min->env, min->cmd, &(min->exec_cmd), 0) == FAIL)
    min->exit = 1;
  else if (!strncmp(min->cmd, "setenv", strlen("setenv")))
    min->env = my_setenv(min->env, &(min->cmd[6]), min, 0);
  else if (!strncmp(min->cmd, "unsetenv", strlen("unsetenv")))
    min->env = my_unsetenv(min->env, min->cmd, min, 0);
  else if (!strcmp(min->cmd, "history") || !strcmp(min->cmd, "history -c"))
    my_history(min);
  else
    do_others(min);
  if ((min->redir1 || min->redir2) &&
      end_redirection(min, &(min->redir1), &(min->redir2), 0) == FAIL)
    min->exit = 1;
  return (OK);
}
