/*
** open_conf.c for 42sh in /home/hoarau_s/42SH/42-shell/Stephen/alias
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Thu May  3 04:41:38 2012 stephen hoarau
** Last update Wed May 23 16:31:07 2012 stephen hoarau
*/

#include "42.h"

int		xopen_conf()
{
  int		fd;

  fd = open(CONF_FILE, O_RDWR);
  if (fd == -1)
    return (-1);
  return (fd);
}
