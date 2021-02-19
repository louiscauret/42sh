/*
** path.c for autocomp in /home/hoarau_s/42SH/autocompletion
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Thu Apr  5 00:12:15 2012 stephen hoarau
** Last update Sun May 20 15:58:43 2012 damien delbos
*/

#include "42.h"

static int	get_number_back(char *line)
{
  int		i;
  int		count;

  i = 0;
  count = 0;
  while (line[i])
    {
      if (line[i] == '.' && line[i + 1] == '.')
	count++;
      i++;
    }
  return (count);
}

static void	modif_path(char *tmp[2])
{
  int		len;
  int		tmp2;
  int		count;

  len = strlen(tmp[0]);
  count = get_number_back(tmp[1]);
  tmp2 = 0;
  while (len != 0 && tmp2 != count)
    {
      if (tmp[0][len] == '/' && tmp[0][len + 1] != '\0')
	{
	  tmp2++;
	  tmp[0][len] = '\0';
	}
      len--;
    }
  tmp[1] += 3 * count;
}

static int	local_dir(char *tmp[2], int slash)
{
  if (!(tmp[0] = my_concat(tmp[0], "/")))
    return (FAIL);
  tmp[0] = strncat(tmp[0], tmp[1], slash);
  tmp[1] = tmp[1] + slash + 1;
  return (OK);
}

static int	absolute_path(char *tmp[2])
{
  int		i;
  int		tmp2;

  i = 0;
  tmp2 = 0;
  while (tmp[1][i])
    {
      if (tmp[1][i] == '/')
	tmp2 = i;
      i++;
    }
  tmp[0] = strcpy(tmp[0], tmp[1]);
  tmp[0][tmp2] = '\0';
  tmp[1] += tmp2 + 1;
  return (OK);
}

int		manage_path(char *tmp[2])
{
  int		i;
  int		tmp2;

  i = 0;
  tmp2 = 0;
  if (tmp[1][0] == '/')
    return (absolute_path(tmp));
  else if (tmp[1][0] == '.' && tmp[1][1] == '/')
    tmp[1] += 2;
  else if (tmp[1][0] == '.' && tmp[1][1] == '.')
    modif_path(tmp);
  else if ((hidenp(tmp[1], "/")) == 0)
    {
      while (tmp[1][i])
	{
	  if (tmp[1][i] == '/')
	    tmp2 += i;
	  i++;
	}
      if (local_dir(tmp, tmp2) == FAIL)
	return (FAIL);
    }
  return (OK);
}
