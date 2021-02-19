/*
** get_next_line.c for get_next_line.c in /home/delbos_d//Projets/42-SH/Rendu
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Fri Apr 27 14:49:32 2012 damien delbos
** Last update Mon May  7 03:52:52 2012 damien delbos
*/

#include "42.h"

static int	my_strlen(char *str)
{
  int		i;

  i = 0;
  while (str[i])
    ++i;
  return (i);
}

static void	fill_buff(char *buffer, int cur, int len)
{
  int		i;

  if (buffer[cur] == '\n')
    cur++;
  i = 0;
  while (cur < len)
    buffer[i++] = buffer[cur++];
  while (i < SIZE_STR_READ)
    buffer[i++] = 0;
}

static int	read_buff(char *ret, char *buffer, int *i)
{
  *i = 0;
  if (!ret)
    return (1);
  while (buffer[*i])
    {
      if (buffer[*i] == '\n' || *i == SIZE_MAX_BUFFER)
	{
	  ret[*i] = 0;
	  fill_buff(buffer, *i, my_strlen(buffer));
	  return (1);
	}
      else
	{
	  ret[*i] = buffer[*i];
	  *i += 1;
	}
    }
  return (0);
}

static char	*gnl_returns(char *ret, char *buffer, int i)
{
  if (i == 0)
    return (NULL);
  ret[i] = 0;
  fill_buff(buffer, i, my_strlen(buffer));
  return (ret);
}

char		*get_next_line(int fd)
{
  static char	buffer[SIZE_STR_READ + 1];
  char		*ret;
  int		i;
  int		j;
  int		read_chars;

  ret = fmalloc(SIZE_MAX_BUFFER + 1);
  if (read_buff(ret, buffer, &i))
    return (ret);
  while ((read_chars = my_read(fd, buffer, SIZE_STR_READ)) > 0)
    {
      j = 0;
      while (j < read_chars)
	{
	  if (buffer[j] == '\n' || i == SIZE_MAX_BUFFER)
	    {
	      ret[i] = 0;
	      fill_buff(buffer, j, read_chars);
	      return (ret);
	    }
	  else
	    ret[i++] = buffer[j++];
	}
    }
  return (gnl_returns(ret, buffer, i));
}
