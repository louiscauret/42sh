/*
** tilde.c for tilde in /home/serra_r//42-shell/Rendu
**
** Made by romain serra
** Login   <serra_r@epitech.net>
**
** Started on  Thu May 10 14:49:03 2012 romain serra
** Last update Sun May 20 16:39:55 2012 stephen hoarau
*/

#include "42.h"

static int	condition_tilde(char *cmd, int compt)
{
  if (cmd[compt] && (cmd[compt] != '~' || compt != 0) &&
      (cmd[compt] != '~' || cmd[compt - 1] != '/') &&
      (cmd[compt] != '~' || cmd[compt - 1] != ' ') &&
      (cmd[compt] != '~' || cmd[compt - 1] != '\t'))
    return (1);
  return (0);
}

static int	test_tilde(char *cmd, int *nb, int *j)
{
  int		compt;

  *nb = 0;
  *j = 0;
  compt = 0;
  while (condition_tilde(cmd, compt))
    compt++;
  if (!cmd[compt])
    return (0);
  return (1);
}

int		loop_tilde(char *cmd, char *str, int compt)
{
  while (condition_tilde(cmd, compt))
    {
      str[compt] = cmd[compt];
      ++compt;
    }
  return (compt);
}

char		*manag_tilde(char *cmd, char **env, int compt, int i)
{
  char		*home;
  char		*str;
  int		j;

  if (env == NULL || (home = get_env(env, "HOME")) == NULL)
    return (cmd);
  while (cmd)
    {
      if (test_tilde(cmd, &compt, &j) == 0)
        return (cmd);
      if (!(str = fmalloc(strlen(home) + strlen(cmd))))
        return (NULL);
      compt = loop_tilde(cmd, str, compt);
      i = compt + 1;
      while (home[j])
        str[compt++] = home[j++];
      if (str[compt - 1] == '/' && cmd[i] == '/')
        --compt;
      my_strcpy(&str[compt], &cmd[i]);
      free(cmd);
      cmd = str;
    }
  return (NULL);
}
