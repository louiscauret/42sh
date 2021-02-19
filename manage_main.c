/*
** manag_main.c for manag_main in /home/delbos_d//Projets/42-SH/Rendu
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Fri Apr 27 16:47:50 2012 damien delbos
** Last update Thu May 24 15:16:33 2012 stephen hoarau
*/

#include "42.h"

int		catch_sign()
{
  if (signal(SIGINT, sign_call) == SIG_ERR ||
      signal(SIGQUIT, sign_call) == SIG_ERR)
    return (FAIL);
  return (OK);
}

int		manag_path(t_minish *min, int i)
{
  i = 0;
  while (min->env && min->env[i] && strncmp(min->env[i], "PATH=", 5) != 0)
    i++;
  if (min->env && min->env[i])
    {
      if (!(min->path = my_str_to_wordtab(&min->env[i][5], ':')))
	return (FAIL);
    }
  else
    min->path = NULL;
  if (min->path == NULL)
    {
      if (!(min->path = fmalloc(2 * sizeof(*min->path))) && (min->exit = 1))
        return (FAIL);
      min->path[0] = 0;
    }
  return (OK);
}

int		if_builtin(char *cmd, int *err)
{
  if (srch_blt(cmd, "exit", err) || srch_blt(cmd, "env", err) ||
      srch_blt(cmd, "setenv", err) || srch_blt(cmd, "unsetenv", err) ||
      srch_blt(cmd, "cd", err) || srch_blt(cmd, "history", err) ||
      srch_blt(cmd, "echo", err) || srch_blt(cmd, "alias", err) ||
      srch_blt(cmd, "unalias", err))
    return (1);
  return (0);
}

int		init_var_to_main(char **env, t_minish *min)
{
  int		i;

  i = 0;
  while (i < MAX_SIZE_CMD)
    min->ctrl_k[i++] = 0;
  min->env = env;
  min->path = NULL;
  min->init = 0;
  min->exit = 0;
  min->nb_exit = FAIL;
  if (!(min->cd_m = xstrdup(".")))
    return (FAIL);
  return (OK);
}

int		recover_cmd(t_minish *min, int *i, int *j)
{
  t_recov	recov;
  char		*cmd_cpy;

  *i = 0;
  *j = 0;
  min->list_cmd = NULL;
  if (catch_sign() == FAIL)
    return (FAIL);
  min->init++;
  sign_call(0);
  min->gnl = recover_struct_term(&(min->t_prev));
  if (!(min->cmd = manag_recovering_cmd(min->env, &recov, min->t_prev, min)))
    return (FAIL);
  if (min->gnl == OK && my_kill_keyboard(0, min->t_prev) == FAIL)
    return (FAIL);
  min->cmd = clean_str(clean_quot((cmd_cpy = min->cmd)));
  if ((*min->cmd && (fill_history(min->cmd, min->env) == FAIL ||
		     pre_apply(min, cmd_cpy) == FAIL)))
    return (FAIL);
  return (OK);
}
