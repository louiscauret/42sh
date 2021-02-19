/*
** tools_4.c for tools_4 in /home/delbos_d//Projets/42-SH/Rendu
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Mon Apr 16 11:12:05 2012 damien delbos
** Last update Wed May 23 21:05:14 2012 damien delbos
*/

#include "42.h"

int		my_error(char *str, int nb)
{
  if (write(2, str, strlen(str)) == -1)
    return (-1);
  return (nb);
}

int		srch_blt(char *cmd, char *built, int *err)
{
  char		**tbl;
  int		i;

  i = 0;
  *err = 0;
  if (!(tbl = my_str_to_wordtab(cmd, ' ')) && (*err = 1) == 1)
    return (1);
  while (tbl[i])
    i++;
  i = 0;
  while (tbl[i] && strcmp(tbl[i], "|"))
    {
      if (!strcmp(tbl[i], built))
	{
	  my_free_tblstr(tbl);
	  return (1);
	}
      ++i;
    }
  my_free_tblstr(tbl);
  return (0);
}

static int	manag_write_invalid_cmd(int nb_exit)
{
  if (my_error(ERR_VOID_CMD, 1) == -1)
    return (nb_exit);
  return (nb_exit + 1);
}

int		test_invalid_cmd(char **cmd, int nb_exit)
{
  char		**and;
  int		i;

  while (cmd && *cmd)
    {
      i = 0;
      if (!(**cmd))
	return (manag_write_invalid_cmd(nb_exit));
      if (!(and = my_str_to_wordtab_bin(*cmd, '&')))
	return (nb_exit);
      while (and[i])
	{
	  if (!(*and[i]))
	    return (manag_write_invalid_cmd(nb_exit));
	  ++i;
	}
      ++cmd;
    }
  return (nb_exit - 1);
}
