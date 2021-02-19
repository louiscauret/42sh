/*
** my_echo_bis.c for my_echo in /home/terrac_l//42-shell/Luc
**
** Made by luc terracher
** Login   <terrac_l@epitech.net>
**
** Started on  Thu Apr  5 03:31:45 2012 luc terracher
** Last update Sun May 20 15:50:31 2012 louis cauret
*/

#include "42.h"

static int	count_size_var_env(char *cmd)
{
  int		i;

  i = 0;
  while (cmd[i] && ((cmd[i] >= '0' && cmd[i] <= '9') ||
                    (cmd[i] >= 'A' && cmd[i] <= 'Z') ||
		    (cmd[i] >= 'a' && cmd[i] <= 'z')
                    || cmd[i] == '_' || cmd[i] == '-'))
    i++;
  return (i);
}

static char	*recover_var_env(char *cmd)
{
  char		*env;

  if (!(env = fmalloc(count_size_var_env(cmd) + 1)))
    return (NULL);
  strncpy(env, &cmd[1], count_size_var_env(&cmd[1]));
  return (env);
}

static char	*check_var_env(char **env, char *str_env, int *quit)
{
  int		i;
  int		x;

  x = 0;
  i = 0;
  *quit = OK;
  while (env[i] && (strncmp(env[i], str_env, strlen(str_env)) ||
		    env[i][strlen(str_env)] != '='))
    i++;
  if (env[i])
    {
      while (env[i][x] && env[i][x] != '=')
	x++;
      return (&env[i][++x]);
    }
  if ((my_error(str_env, 0) == -1 || my_error(ERR_UNDEF_VAR, 0) == -1) &&
      (*quit = FAIL) == FAIL)
    return (NULL);
  return (NULL);
}

static char	*change_var_env(char *str_env, char *cmd, int i, char *name_var)
{
  char		*res;

  if (!(res = fmalloc(strlen(str_env) + strlen(cmd) + 1)))
    return (NULL);
  strncpy(res, cmd, i);
  strcpy(&res[i], str_env);
  cmd += i + strlen(name_var) + 1;
  strcpy(&res[strlen(res)], cmd);
  return (res);
}

char		*replace_to_var_env(char *cmd, char **env)
{
  int		i;
  char		*str_env;
  char		*name_var;
  int		quit;

  i = 0;
  while (cmd[i])
    {
      if (cmd[i + 1] && cmd[i] == '$' && cmd[i + 1] != ' ' &&
	  cmd[i + 1] != '\t')
	{
	  if (!(name_var = recover_var_env(&cmd[i])))
	    return (NULL);
	  if (!(str_env = check_var_env(env, name_var, &quit)) && quit == FAIL)
	    return (NULL);
	  if (str_env && !(cmd = change_var_env(str_env, cmd, i, name_var)))
	    return (NULL);
	}
      i++;
    }
  return (cmd);
}
