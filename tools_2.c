/*
** tools_2.c for tool_2 in /home/delbos_d//Projets/MiniShell_2
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Mon Feb 27 14:08:00 2012 damien delbos
** Last update Sun May 20 16:43:57 2012 stephen hoarau
*/

#include "42.h"

int		my_open(const char *pathname, int flags, mode_t mode)
{
  int		fd;

  if ((fd = open(pathname, flags, mode)) == -1)
    perror("Open:");
  return (fd);
}

int		my_dup2(int fd_0, int fd_1)
{
  int		fd;

  if ((fd = dup2(fd_0, fd_1)) == -1)
    my_error(ERR_DUP2, 1);
  return (fd);
}

int		my_close(int fd)
{
  if (close(fd) == -1)
    {
      my_error(ERR_CLOSE, 1);
      return (-1);
    }
  return (1);
}

int		my_read(int fd, char *buf, int nb)
{
  ssize_t	ret;

  if ((ret = read(fd, buf, nb)) == -1)
    my_error(ERR_READ, 1);
  return (ret);
}

int		my_pipe(int *fd)
{
  if (pipe(fd) == -1)
    {
      my_error(ERR_PIPE, 1);
      return (-1);
    }
  return (1);
}
