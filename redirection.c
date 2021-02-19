/*
** redirection.c for redirection in /home/delbos_d//Projets/MiniShell_2
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Tue Feb 28 19:44:59 2012 damien delbos
** Last update Sun May 20 15:49:07 2012 stephen hoarau
*/

#include "42.h"

int		redir_right(t_minish *min, int i, int *redir)
{
  char		*match;

  cut_redir(min, ">");
  match = recover_match(min, i, NULL);
  if (!match && my_error(ERR_MISS_REDIR, 1) && (min->exit = 1))
    return (FAIL);
  if ((min->fd_right = my_open(match, O_WRONLY | O_CREAT | O_TRUNC,
			       S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1 ||
      my_dup2(min->fd_right, 1) == -1)
    return (FAIL);
  *redir = 1;
  return (OK);
}

int		redir_dbl_right(t_minish *min, int i, int *redir)
{
  char		c;
  int		ret;
  char		*match;

  cut_redir(min, ">>");
  match = recover_match(min, i, NULL);
  if (!match && my_error(ERR_MISS_REDIR, 1) && (min->exit = 1))
    return (FAIL);
  if ((min->fd_right = my_open(match, O_RDWR | O_CREAT,
			       S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    return (FAIL);
  while ((ret = my_read(min->fd_right, &c, 1)) > 0);
  if (ret == -1 || my_dup2(min->fd_right, 1) == -1)
    return (FAIL);
  *redir = 1;
  return (OK);
}

static int	redir_dbl_left_2(t_minish *min, char *match, char *str,
				 int boucle)
{
  char		*ret;

  if (!(str = fmalloc(SIZE_MAX_BUFFER)))
    return (FAIL);
  while (boucle)
    {
      if (my_write(1, "? ", 2) == -1)
	return (FAIL);
      if (!(ret = get_next_line(0)) && (min->exit = 1))
	return (my_write(1, "\n", 1));
      if (!strcmp(ret, match))
        boucle = 0;
      if (boucle && (strlen(ret) + strlen(str) + 2) < SIZE_MAX_BUFFER)
        {
          strcat(str, ret);
          strcat(str, "\n");
        }
    }
  if (my_pipe(min->fd) == -1 || my_write(min->fd[1], str, strlen(str)) == -1
      || my_close(min->fd[1]) == -1 || my_dup2(min->fd[0], 0) == -1)
    return (FAIL);
  free(ret);
  free(str);
  return (OK);
}

int		redir_dbl_left(t_minish *min, int i, int *redir)
{
  char		*match;

  *redir = 0;
  cut_redir(min, "<<");
  match = recover_match(min, i, NULL);
  if (!match && my_error(ERR_MISS_REDIR, 1) && (min->exit = 1))
    return (FAIL);
  if (redir_dbl_left_2(min, match, NULL, 1) == FAIL && (min->exit = 1))
    return (FAIL);
  if (min->exit == 0)
    *redir = 2;
  return (OK);
}

int		redir_left(t_minish *min, int i, int *redir)
{
  char		*match;

  cut_redir(min, "<");
  match = recover_match(min, i, NULL);
  if (!match && my_error(ERR_MISS_REDIR, 1) && (min->exit = 1))
    return (FAIL);
  if ((min->fd_left = my_open(match, O_RDONLY, 0)) == -1 ||
      my_dup2(min->fd_left, 0) == -1)
    return (FAIL);
  *redir = 3;
  return (OK);
}
