/*
** my_getnbr_base.c for my_getnbr_base in /home/delbos_d//Projets/Bistromathique
** 
** Made by damien delbos
** Login   <delbos_d@epitech.net>
** 
** Started on  Sat Nov 12 23:34:11 2011 damien delbos
** Last update Sun May 20 16:10:27 2012 louis cauret
*/

#include "42.h"

static int	my_dec_value(char c, char *base)
{
  int		i;

  i = 0;
  while (base[i] != c)
    i++;
  return (i);
}

static int	fpower_p(int nb, int power, int poweract, int nbinit)
{
  if (nb < 0)
    return (0);
  if (poweract >= power)
    return (nb);
  nb *= nbinit;
  poweract++;
  nb = fpower_p(nb, power, poweract, nbinit);
  return (nb);
}

static int	my_power(int nb, int power)
{
  if (power == 0)
    return (1);
  if (nb == 0 || power < 0)
    return (0);
  if (nb > 0)
    {
      nb = fpower_p(nb, power, 1, nb);
      return (nb);
    }
  return (0);
}

int		my_getnbr_base(char *str, char *base)
{
  int		i;
  int		nb;
  int		len;
  int		pos;

  i = 0;
  nb = 0;
  len = strlen(base);
  pos = strlen(str) - 1;
  while (str[i])
    {
      if (str[i] >= base[0] && str[i] <= base[len - 1])
	{
	  nb += (my_dec_value(str[i], base) * my_power(len, pos));
	  i++;
	  pos--;
	}
      else
	i++;
    }
  return (nb);
}
