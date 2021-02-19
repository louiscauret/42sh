/*
** getenv.c for autocompl in /home/hoarau_s/42SH/autocompletion/lib/my
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Wed Apr  4 22:10:33 2012 stephen hoarau
** Last update Sun May  6 18:45:35 2012 damien delbos
*/

#include "42.h"

char		*get_env(char **envp, char *line)
{
  int		i;
  char		**env;

  i = 0;
  env = NULL;
  while (envp[i])
    {
      if ((strncmp(line, envp[i], strlen(line)) == 0))
	{
	  if (!(env = my_str_to_wordtab(envp[i], '=')))
	    return (NULL);
	  return (env[1]);
	}
      i++;
    }
  return (NULL);
}
