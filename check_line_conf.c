/*
** check_line_conf.c for 42sh in /home/hoarau_s/42SH/42-shell/Rendu
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Tue May 15 16:06:45 2012 stephen hoarau
** Last update Sun May 20 15:54:58 2012 luc terracher
*/

#include "42.h"

void		check_first_quote(char *buffer, int line, char *path)
{
  int		i;

  i = 0;
  while (buffer[i])
    {
      if (buffer[i] == '=')
	{
	  while (buffer[i] == '=')
	    i++;
	  if (buffer[i] != '\'')
	    {
	      printf("%s:%d:Missing ' at start of an alias declaration.\n",
		     path, line);
	      return ;
	    }
	  return ;
	}
      i++;
    }
}

void		check_wrong_alias(char *buffer, int line, char *path)
{
  int		i;
  int		equal;

  i = 0;
  equal = 0;
  while (buffer[i])
    if (buffer[i++] == '=')
      equal++;
  if (equal == 0)
    {
      fprintf(stderr, "%s:%d:Missing operand \'=\' between alias.\n",
	     path, line);
      return ;
    }
  if (buffer[strlen(buffer) - 1] != '\'')
    {
      printf("%s:%d:Missing ' after alias.\n", path, line);
      return ;
    }
  check_first_quote(buffer, line, path);
}

static void	display_error(char **env, int line, char *buffer)
{
  fprintf(stderr, "%s:%d: ", my_concat(get_env(env, "HOME"), CONF_FILE), line);
  fprintf(stderr, "Alias non valid\n");
  buffer = 0;
}

void		verif_conf_file(char **env)
{
  int		fd;
  int		i;
  char		*buffer;

  if (env == NULL || env[0] == NULL)
    return ;
  i = 1;
  if ((fd = xopen_conf(env)) == -1)
    return ;
  while ((buffer = get_next_line(fd)) != NULL)
    {
      if (buffer[0] != '#' && buffer[0] != '\0')
	{
	  if (strncmp("alias ", buffer, 6) && strncmp("alias\t", buffer, 6))
	    display_error(env, i, buffer);
	  else
	    check_wrong_alias(buffer, i, my_concat(get_env(env, "HOME"),
						   CONF_FILE));
	}
      free(buffer);
      i++;
    }
  if (close(fd) == -1)
    return ;
}

int		check_line_conf(char *line)
{
  int		i;

  if (strncmp("alias ", line, 6) && strncmp("alias\t", line, 6))
    return (0);
  if (line[strlen(line) - 1] != '\'')
    return (0);
  i = 0;
  while (line[i])
    {
      if (line[i] == '=')
	{
	  while (line[i] == '=')
	    i++;
	  if (line[i] == '\'')
	    return (1);
	  else
	    return (0);
	}
      i++;
    }
  return (0);
}
