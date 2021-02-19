/*
** my_fcpy_env.c for fcpy in /home/serra_r//42-shell/Rendu
** 
** Made by romain serra
** Login   <serra_r@epitech.net>
** 
** Started on  Mon May 14 14:36:27 2012 romain serra
** Last update Sun May 20 16:08:47 2012 louis cauret
*/

#include "42.h"

static int	my_strlen_m(char *cmd)
{
  int		i;

  i = 0;
  while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t')
    i++;
  return (i);
}

static int	check_variable(char **env, char *cmd, int *verif)
{
  int		i;

  i = 0;
  *verif = OK;
  while (env && env[i])
    {
      if (strncmp(env[i], cmd, my_strlen_m(cmd)) == 0)
	return (1);
      i++;
    }
  if (my_write(2, cmd, my_strlen_m(cmd)) == -1 ||
      my_error(ERR_UNDEF_VAR, 0) == -1)
    *verif = FAIL;
  return (0);
}

char		**my_fcpy_env(char **env, char *cmd, int *quit, int i)
{
  char		**tbl;
  int		j;
  int		verif;

  j = 0;
  cmd = clean_str(cmd);
  if ((!check_variable(env, cmd, &verif) && (*quit = OK) == OK) ||
      (verif == FAIL && (*quit = FAIL) == FAIL))
    return (NULL);
  if (!(tbl = fmalloc(my_strlen_tbl(env) * sizeof (*env))) &&
      (*quit = FAIL) == FAIL)
    return (NULL);
  while (env[i])
    {
      if (strncmp(env[i], cmd, my_strlen_m(cmd)) == 0)
	i++;
      else
	{
	  if (!(tbl[j] = fmalloc(strlen(env[i]))) && (*quit = FAIL) == FAIL)
	    return (NULL);
	  strcpy(tbl[j++], env[i++]);
	}
    }
  return (tbl);
}
