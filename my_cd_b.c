/*
** my_cd_b.c for my_cd_b in /home/delbos_d//Projets/MiniShell_2
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Wed Dec 28 10:25:28 2011 damien delbos
** Last update Wed May 23 20:55:34 2012 damien delbos
*/

#include "42.h"

static int	check_dir(char *path)
{
  struct stat	s;

  if (lstat(path, &s) == -1)
    return (-1);
  if ((s.st_mode & S_IFDIR) == 0)
    {
      if (my_write(2, path, strlen(path)) == -1 ||
	  my_error(": Not a directory.\n", 1) == -1)
	return (-1);
    }
  return (1);
}

static int	cd_error(char *path)
{
  if (!access(path, F_OK) && access(path, R_OK) == -1)
    {
      if (my_write(2, path, strlen(path)) == -1 ||
	  my_error(": Permission denied.\n", 1) == -1)
	return (-1);
    }
  else if (access(path, F_OK) == -1)
    {
      if (my_write(2, path, strlen(path)) == -1 ||
	  my_error(": No such file or directory.\n", 1) == -1)
	return (-1);
    }
  else if (check_dir(path) == -1)
    return (-1);
  return (1);
}

static char	**manag_cd_simple(char **env, t_minish *min)
{
  char		*home;
  int		i;

  i = 0;
  while (env[i] && strncmp(env[i], "HOME=", strlen("HOME=")))
    i++;
  if (env[i] == NULL)
    {
      if (my_error(ERR_HOME, 1) == -1)
	min->exit = 1;
      return (env);
    }
  if (!(home = strdup(&env[i][5])))
    return (NULL);
  if (!(env = change_env(env, home, 0, min)) && (min->exit = 1))
    return (NULL);
  if (chdir(&env[i][5]) == -1 && ((my_error(ERR_CD, 1) == -1 &&
				   (min->exit = 1)) || 1))
    return (env);
  return (env);
}

char		**my_cd(char *dir, char **env, t_minish *min)
{
  while ((*dir == ' ' || *dir == '\t') &&
	 (!dir[1] || dir[1] == ' ' || dir[1] == '\t'))
    dir++;
  if (*dir == 0)
    return (manag_cd_simple(env, min));
  else if (*dir == ' ')
    {
      dir++;
      if ((*dir == '-' && !dir[1] && chdir(min->cd_m) == -1) ||
	  (*dir != '-' && chdir(dir) == -1))
	{
	  if ((cd_error(dir) == -1 && (min->exit = 1)) || 1)
	    return (env);
	}
      else
	if (!(env = change_env(env, dir, 0, min)) && (min->exit = 1))
	  return (NULL);
    }
  else
    if ((my_error("cd", 1) == -1 || my_error(dir, 1) == -1 ||
	 my_error(ERR_CMD_NF, 1) == -1) && (min->exit = 1))
      return (NULL);
  return (env);
}
