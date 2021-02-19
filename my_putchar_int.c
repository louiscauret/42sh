/*
** my_putchar_int.c for my_putchar_int in /home/delbos_d//Library/Libtermcap
** 
** Made by damien delbos
** Login   <delbos_d@epitech.net>
** 
** Started on  Tue Jan 17 21:51:11 2012 damien delbos
** Last update Mon May  7 03:07:50 2012 damien delbos
*/

#include "42.h"

int	my_putchar_int(int nb)
{
  char	c;

  c = nb;
  if (my_write(0, &c, 1) == -1)
    return (-1);
  return (nb);
}
