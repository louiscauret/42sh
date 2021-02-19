/*
** manage_redirects.c for manage_redirects in /home/delbos_d//Projets/42-SH/svn_42sh/Rattrapage
** 
** Made by damien delbos
** Login   <delbos_d@epitech.net>
** 
** Started on  Wed May 23 21:02:09 2012 damien delbos
** Last update Wed May 23 21:02:10 2012 damien delbos
*/

#include "42.h"

static int	test_redir(t_minish *min, int disp, int *r, int *l)
{
  int		i;

  i = 0;
  while (min->tmp[i] && *r <= 1 && *l <= 1)
    {
      while (min->tmp[i] && min->tmp[i][0] != '<' && min->tmp[i][0] != '>')
	++i;
      if (min->tmp[i] && ((!strcmp(min->tmp[i], "<<")) ||
			  !strcmp(min->tmp[i], "<")))
	++(*l);
      if (min->tmp[i] && ((!strcmp(min->tmp[i], ">>")) ||
			  !strcmp(min->tmp[i], ">")))
	++(*r);
      if (min->tmp[i] &&
	  ((min->tmp[i][0] == '<' && np_char(min->tmp, i, 0, 0) == '|') ||
	   (min->tmp[i][0] == '>' && np_char(min->tmp, i, 1, 0) == '|')))
	++(*l);
      if (min->tmp[i])
	++i;
    }
  if (disp && (*r > 1 || *l > 1) && my_error(ERR_AMB_REDIR, 1))
    return (FAIL);
  return (OK);
}

static int	manag_redirection_2(t_minish *min, int *redir, int i)
{
  if (min->tmp[i] && !strcmp(min->tmp[i], "<<"))
    return (redir_dbl_left(min, i, redir));
  else if (min->tmp[i] && !strcmp(min->tmp[i], ">"))
    return (redir_right(min, i, redir));
  else if (min->tmp[i] && !strcmp(min->tmp[i], ">>"))
    return (redir_dbl_right(min, i, redir));
  else if (min->tmp[i] && !strcmp(min->tmp[i], "<"))
    return (redir_left(min, i, redir));
  return (OK);
}

int		manag_redirection(t_minish *min, int *redir1, int *redir2,
				  int i)
{
  int		left;
  int		right;

  if (!(*redir1 = 0) && !(*redir2 = 0) && !(right = 0) && !(left = 0) &&
      (test_redir(min, 1, &right, &left) == FAIL || !min->tmp))
    return (FAIL);
  while (min->tmp[i] &&
	 strcmp(min->tmp[i], "<") && strcmp(min->tmp[i], "<<") &&
	 (strcmp(min->tmp[i], ">>") || left != 0) &&
	 (strcmp(min->tmp[i], ">") || left != 0))
    ++i;
  if (!min->tmp[i])
    return (OK);
  if (manag_redirection_2(min, redir1, i) == FAIL)
    return (FAIL);
  i = 0;
  while (min->tmp[i] &&
	 strcmp(min->tmp[i], ">") && strcmp(min->tmp[i], "<<") &&
         strcmp(min->tmp[i], ">>") && strcmp(min->tmp[i], "<"))
    ++i;
  if (!min->tmp[i])
    return (OK);
  if (manag_redirection_2(min, redir2, i) == FAIL)
    return (FAIL);
  return (OK);
}

int		end_redirection(t_minish *min, int *redir1, int *redir2,
				int opt)
{
  if ((*redir1 == 1 && (*redir1 = 0) == 0) ||
      (*redir2 == 1 && (*redir2 = 0) == 0))
    if (my_dup2(0, 1) == -1 || my_close(min->fd_right) == -1)
      return (FAIL);
  if (opt && ((*redir1 == 2 && (*redir1 = 0) == 0) ||
	      (*redir2 == 2 && (*redir2 = 0) == 0)))
    if (my_dup2(0, min->fd[0]) == -1 || my_close(min->fd[0]) == -1)
      return (FAIL);
  if ((*redir1 == 3 && (*redir1 = 0) == 0) ||
      (*redir2 == 3 && (*redir2 = 0) == 0))
    if (my_dup2(0, 1) == -1 || my_close(min->fd_left) == -1)
      return (FAIL);
  return (OK);
}
