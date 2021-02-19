/*
** recover_cmd_2.c for recover_cmd_2 in /home/delbos_d//Projets/42-SH/Rendu
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Thu Apr  5 10:42:30 2012 damien delbos
** Last update Thu May 24 14:02:02 2012 stephen hoarau
*/

#include "42.h"

int		refresh_tab(t_recov *recov, char *name_term)
{
  name_term = 0;
  if (manag_input() == -1 ||
      my_write(1, recov->str, strlen(recov->str)) == -1)
    return (FAIL);
  recov->i = strlen(recov->str);
  return (OK);
}
