/*
** my_set_unset_env_b.c for my_set_unset_env_b in /home/delbos_d//Projets/42-SH/svn_42sh/Rattrapage
** 
** Made by damien delbos
** Login   <delbos_d@epitech.net>
** 
** Started on  Wed May 23 20:42:29 2012 damien delbos
** Last update Wed May 23 21:29:42 2012 damien delbos
*/

#include "42.h"

static char	**add_str_to_tblstr(char **env, char *env_name)
{
  int		i;
  int		size;
  char		**res;

  i = 0;
  size = 0;
  while (env[size] != NULL)
    size++;
  if (!(res = (char **)fmalloc((size + 2) * sizeof(*res))))
    return (NULL);
  while (i < size)
    {
      if (!(res[i] = fmalloc(strlen(env[i]) + 1)))
        return (NULL);
      strcpy(res[i], env[i]);
      i++;
    }
  if (!(res[i] = fmalloc(strlen(env_name) + 1)))
    return (NULL);
  strcpy(res[i++], env_name);
  res[i] = 0;
  return (res);
}

static char	**my_setenv_2(char **env, char *cmd, int i, char *env_name)
{
  int		j;

  j = 0;
  env_name[i++] = '=';
  while (env && env[j] && strncmp(env[j], env_name, strlen(env_name)) != 0)
    j++;
  if (*(cmd++))
    {
      if (*cmd == '"')
	cmd++;
      while (*cmd && *cmd != '"')
	env_name[i++] = *(cmd++);
    }
  if (env && env[j])
    strcpy(env[j], env_name);
  else if (env && !env[j])
    env = add_str_to_tblstr(env, env_name);
  else
    {
      if (!(env = fmalloc(2 * sizeof(char *)))
	  || !(env[j] = fmalloc(strlen(env_name) + 1)))
	return (NULL);
      strcpy(env[j], env_name);
    }
  return (env);
}

char		**my_setenv(char **env, char *cmd, t_minish *min, int i)
{
  char		*env_name;

  cmd = clean_str(cmd);
  if (*cmd == 0 && my_env(env, "env", &(min->exec_cmd), 0) == FAIL &&
      (min->exit = 1))
    return (NULL);
  else if (*cmd)
    {
      if (!(env_name = fmalloc(strlen(cmd) + 1)) && (min->exit = 1))
	return (NULL);
      while (*cmd != ' ' && *cmd)
	env_name[i++] = *(cmd++);
      if (!(env = my_setenv_2(env, cmd, i, env_name)) && (min->exit = 1))
	return (NULL);
    }
  min->exec_cmd = OK;
  return (env);
}

char		**my_unsetenv(char **env, char *env_name, t_minish *min, int i)
{
  if (unsetenv_star(min->cmd))
    return (NULL);
  while (*env_name && *env_name != ' ')
    env_name++;
  if (*env_name)
    env_name++;
  while (env[i] && strncmp(env[i], env_name, strlen(env_name)) != 0)
    i++;
  if (env[i] == 0)
    if ((my_error(env_name, 1) == -1 || my_error(ERR_UN_VAR, 1) == -1) &&
	(min->exit == 1))
      return (env);
  while (env[i])
    {
      env[i] = env[i + 1];
      i++;
    }
  min->exec_cmd = OK;
  return (env);
}
