/*
** manag_env.c for manag_env in /home/delbos_d//Projets/42-SH/Rendu
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Thu May  3 07:49:01 2012 damien delbos
** Last update Sun May 20 15:47:37 2012 louis cauret
*/

#include "42.h"

static char	*manag_racine(char **env, int j, char *new_dir)
{
  char		*res;

  if (!(res = fmalloc(4 + strlen(new_dir) + 1)))
    return (NULL);
  strcpy(res, "PWD=");
  strcpy(&res[4], new_dir);
  env[j] = res;
  *new_dir = 0;
  return (new_dir);
}

static char	*manag_dir(char **env, int j, char *new_dir)
{
  char		*res;

  if (!(res = fmalloc(strlen(env[j]) + my_strlen_cd(new_dir) + 2)))
    return (NULL);
  strcpy(res, env[j]);
  if (res[strlen(res) - 1] != '/')
    strcpy(&res[strlen(res)], "/");
  strncpy(&res[strlen(res)], new_dir, my_strlen_cd(new_dir));
  if (res[strlen(res) - 1] != '/')
    strcpy(&res[strlen(res)], "/");
  env[j] = res;
  new_dir += my_strlen_cd(new_dir) + 1;
  return (new_dir);
}

static char	*manag_post_dir(char **env, int j, char *new_dir,
				int i)
{
  if (strcmp(env[j], "PWD=/"))
    {
      i = strlen(env[j]) - 2;
      env[j][i] = 0;
      while (env[j][i] != '/')
        env[j][i--] = 0;
    }
  while (*new_dir && *new_dir != '/')
    new_dir++;
  if (*new_dir)
    new_dir++;
  return (new_dir);
}

static char	*change_env_2(char **env, char *nwd, int j)
{
  if (*nwd == '/')
    {
      if (!(nwd = manag_racine(env, j, nwd)))
	return (NULL);
    }
  else if ((*nwd >= 'A' && *nwd <= 'Z') || (*nwd >= '0' && *nwd <= '9')
	   || (*nwd >= 'a' && *nwd <= 'z'))
    {
      if (!(nwd = manag_dir(env, j, nwd)))
	return (NULL);
    }
  else if (!strcmp(nwd, "..") || !strncmp(nwd, "../", 3))
    nwd = manag_post_dir(env, j, nwd, 0);
  else
    {
      while (*nwd && *nwd != '/')
	nwd++;
      if (*nwd == '/')
	nwd++;
    }
  return (nwd);
}

char		**change_env(char **env, char *nwd, int j,
			     t_minish *min)
{
  while (env[j] && strncmp(env[j], "PWD=", strlen("PWD=")) != 0)
    j++;
  if (env[j])
    {
      if (!(min->cd_m = xstrdup(&env[j][4])))
	return (NULL);
      while (*nwd)
        {
	  if (!(nwd = change_env_2(env, nwd, j)))
	    return (NULL);
        }
    }
  return (env);
}
