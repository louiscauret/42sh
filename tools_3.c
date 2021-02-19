/*
** tools_3.c for tools_3 in /home/delbos_d//Projets/MiniShell_2
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Fri Mar  2 17:53:40 2012 damien delbos
** Last update Wed May 23 20:19:48 2012 damien delbos
*/

#include "42.h"

int		my_strlen_tbl(char **tbl)
{
  int		i;

  i = 0;
  while (tbl[i])
    i++;
  return (i);
}

int		my_write(int fd, char *str, int nb)
{
  if (write(fd, str, nb) == -1)
    {
      if (write(2, ERR_WRITE, strlen(ERR_WRITE)) == -1)
	return (-1);
      return (-1);
    }
  return (0);
}

void		add_char_in_str(int c, int i, char *cmd)
{
  char		cpy;

  while (cmd[i])
    {
      cpy = cmd[i];
      cmd[i] = c;
      c = cpy;
      i++;
    }
  cmd[i] = c;
}

char		np_char(char **str, int i, int opt, int j)
{
  if (opt == 1)
    {
      while (str[i])
	{
	  ++i;
	  j = 0;
	  while (str[i] && str[i][j] && str[i][j] != '<' && str[i][j] != '>' &&
		 str[i][j] != '|')
	    ++j;
	  if (str[i] && str[i][j])
	    return (str[i][j]);
	}
      return (0);
    }
  while (i >= 0)
    {
      --i;
      j = 0;
      while (i >= 0 && str[i][j] && str[i][j] != '<' && str[i][j] != '>' &&
	     str[i][j] != '|')
	--j;
      if (i >= 0 && str[i][j])
	return (str[i][j]);
    }
  return (0);
}
