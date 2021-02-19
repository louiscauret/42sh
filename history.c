/*
** history.c for history in /home/cauret_l//Systeme_UNIX/42sh_local/42-shell/historique
**
** Made by louis cauret
** Login   <cauret_l@epitech.net>
**
** Started on  Wed Apr  4 23:04:03 2012 louis cauret
** Last update Thu May 24 15:28:17 2012 stephen hoarau
*/

#include "42.h"

int		my_xopen(char **env)
{
  int		fd;
  static char	*pwd = NULL;

  if (!pwd)
    if (!(pwd = get_env(env, "PWD")) || !(pwd = my_concat(pwd, "/")) ||
	!(pwd = my_concat(pwd, FILE)))
      return (-1);
  fd = open(pwd, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  return (fd);
}

static t_hist	*add_hist_in_list(t_hist *hist, char *str)
{
  t_hist	*init;
  t_hist	*add_on;

  init = hist;
  while (hist && hist->next)
    hist = hist->next;
  if (!(add_on = (t_hist *)fmalloc(sizeof(*add_on))))
    return (NULL);
  strncpy(add_on->str, str, MAX_SIZE_CMD - 1);
  add_on->str[MAX_SIZE_CMD - 1] = 0;
  add_on->prev = hist;
  add_on->next = NULL;
  if (!hist)
    return (add_on);
  hist->next = add_on;
  return (init);
}

int		recover_hist_to_list(t_recov *recov, char **env)
{
  char		*str;

  recov->hist = NULL;
  if ((recov->fd_hist = my_xopen(env)) == -1)
    return (OK);
  if ((str = get_next_line(recov->fd_hist)) && *str)
    recov->hist = add_hist_in_list(recov->hist, str);
  while ((str = get_next_line(recov->fd_hist)) && *str)
    recov->hist = add_hist_in_list(recov->hist, str);
  recov->hist = add_hist_in_list(recov->hist, "");
  if (recov->hist == NULL)
    return (FAIL);
  if (my_close(recov->fd_hist) == -1)
    return (FAIL);
  while (recov->hist && recov->hist->next)
    recov->hist = recov->hist->next;
  return (OK);
}

void		render_history(t_recov *recov, int opt, char *name_term)
{
  refresh_line(recov, name_term);
  if (opt == NEXT && (!recov->hist || !recov->hist->next ||
		      *recov->hist->next->str == 0))
    {
      if (recov->hist && recov->hist->next)
	recov->hist = recov->hist->next;
      strncpy(recov->str, recov->str_end, MAX_SIZE_CMD - 1);
    }
  else if (opt == NEXT)
    {
      recov->hist = recov->hist->next;
      strncpy(recov->str, recov->hist->str, MAX_SIZE_CMD - 1);
    }
  else if (opt == PREVIOUS && recov->hist && recov->hist->prev)
    {
      recov->hist = recov->hist->prev;
      strncpy(recov->str, recov->hist->str, MAX_SIZE_CMD - 1);
    }
  recov->str[MAX_SIZE_CMD - 1] = 0;
}

int		fill_history(char *cmd, char **env)
{
  int           fd;

  if ((fd = my_xopen(env)) == -1)
    return (OK);
  while (get_next_line(fd));
  if (my_write(fd, cmd, strlen(cmd)) == -1 || my_write(fd, "\n", 1) == -1 ||
      my_close(fd) == -1)
    return (FAIL);
  return (OK);
}
