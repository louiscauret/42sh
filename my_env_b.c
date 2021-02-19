/*
** my_env_b.c for my_env_b in /home/delbos_d//Projets/42-SH/svn_42sh/Rattrapage
** 
** Made by damien delbos
** Login   <delbos_d@epitech.net>
** 
** Started on  Wed May 23 20:47:30 2012 damien delbos
** Last update Wed May 23 20:47:31 2012 damien delbos
*/

#include "42.h"

static int		my_env_2(char **env, t_minish *min, int *quit,
				 int *exit)
{
  if (!(*exit = 0) && !strncmp(min->cmd, "env -i ", 7))
    {
      min->cmd += 7;
      if (!(min->tmp = my_str_to_wordtab(min->cmd, ' ')))
        return (FAIL);
      min->env = NULL;
      min->path = NULL;
      if (interpret_cmd(min) == FAIL)
        return (FAIL);
    }
  else if (!strncmp(min->cmd, "env -u ", 7) && min->cmd[7])
    {
      min->cmd += 7;
      if (!(min->env = my_fcpy_env(env, min->cmd, quit, 0)) &&
          (*quit == OK || *quit == FAIL) && (*exit = 1))
        return (*quit);
      while (*(min->cmd) && *(min->cmd) != ' ' && *(min->cmd) != '\t')
        (min->cmd)++;
      if (!(min->tmp = my_str_to_wordtab(min->cmd, ' ')))
        return (FAIL);
      min->path = my_str_to_wordtab(get_env(min->env, "PATH"), ':');
      if (interpret_cmd(min) == FAIL)
        return (FAIL);
    }
  return (OK);
}

static int		init_my_env(char **env, char *cmd, t_minish *min)
{
  min->i = 0;
  min->cmd = cmd;
  min->env = env;
  min->exit = 0;
  if (!(min->tmp = my_str_to_wordtab(min->cmd, ' ')))
    return (FAIL);
  if (manag_redirection(min, &(min->redir1), &(min->redir2), 0) == FAIL)
    return (FAIL);
  min->cmd = clean_str(min->cmd);
  return (OK);
}

int			my_env(char **env, char *cmd, int *exec_cmd, int quit)
{
  t_minish		min;
  int			exit;

  if (init_my_env(env, cmd, &min) == FAIL)
    return (FAIL);
  if (!strcmp(min.cmd, "env"))
    {
      while (env && env[min.i])
        if (printf("%s\n", min.env[min.i++]) < 0)
          return (FAIL);
    }
  else if (!strncmp(min.cmd, "env -i ", 7) ||
           (!strncmp(min.cmd, "env -u ", 7) && min.cmd[7]))
    {
      if ((my_env_2(env, &min, &quit, &exit) == FAIL && (quit = FAIL)) || exit)
        return (quit);
    }
  else if (strcmp(min.cmd, "env -i") && strcmp(min.cmd, "env -u"))
    if (my_error(min.cmd, 1) == -1 || my_error(ERR_CMD_NF, 1) == -1)
      return (FAIL);
  if ((min.redir1 || min.redir2) &&
      end_redirection(&min, &min.redir1, &min.redir2, 1) == FAIL)
    return (FAIL);
  *exec_cmd = OK;
  return (OK);
}
