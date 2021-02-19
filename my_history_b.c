/*
** my_history_b.c for my_history_b.c in /home/delbos_d//Projets/42-SH/svn_42sh/Rattrapage
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Wed May 23 20:44:35 2012 damien delbos
** Last update Thu May 24 15:25:36 2012 stephen hoarau
*/

#include "42.h"

static int	my_xopen2(char **env)
{
  int		fd;
  static char	*pwd = NULL;

  if (!pwd)
    if (!(pwd = get_env(env, "PWD"))|| !(pwd = my_concat(pwd, "/")) ||
	!(pwd = my_concat(pwd, FILE)))
      return (-1);
  fd = open(pwd, O_RDWR | O_CREAT | O_TRUNC,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd == -1 && my_error(ERR_OPEN, 1) == -1)
    fd = -1;
  return (fd);
}

static void	my_history_rm(t_minish *min)
{
  int		fd;

  if ((fd = my_xopen2(min->env)) == -1 && (min->exit = 1))
    return ;
  if (my_write(fd, "\n", 1) == -1 && (min->exit = 1))
    return ;
  if (my_close(fd) == -1 && (min->exit = 1))
    return ;
}

void		my_history(t_minish *min)
{
  int		fd;
  char		*str;

  if (!strcmp(clean_str(min->cmd), "history -c"))
    my_history_rm(min);
  else if (!strcmp(clean_str(min->cmd), "history"))
    {
      if ((fd = my_xopen(min->env)) == -1)
        return ;
      while ((str = get_next_line(fd)))
        if (*str && printf("%s\n", str) < 0 && (min->exit = 1))
          return ;
      if (my_close(fd) == -1 && (min->exit = 1))
        return ;
    }
  else
    if (my_error(ERR_HISTORY, 1) == -1 &&
        (min->exit = 1))
      return ;
  min->exec_cmd = OK;
  return ;
}
