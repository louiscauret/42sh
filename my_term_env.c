/*
** my_term_env.c for my_term_env in /home/delbos_d//Projets/Alum_1
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Thu Jan 19 12:53:52 2012 damien delbos
** Last update Sun May 20 15:54:04 2012 damien delbos
*/

#include "42.h"

char	*my_term_env(char **env, int ac)
{
  int	i;

  i = 0;
  if (ac == 1 || env == NULL)
    return (NULL);
  while (env[i] && strncmp(env[i], "TERM=", 5))
    i++;
  if (env[i])
    return (&env[i][5]);
  return (NULL);
}
