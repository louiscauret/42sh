/*
** recover_cmd_3.c for recover_cmd_3 in /home/delbos_d//Projets/42-SH/Rendu
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Wed May 16 09:42:10 2012 damien delbos
** Last update Sun May 20 15:35:39 2012 stephen hoarau
*/

#include "42.h"

static const int	g_key[] =
  {
    ENTREE,
    BCKSPACE,
    CTRL_E,
    F_DROITE,
    F_GAUCHE,
    F_BAS,
    F_HAUT,
    CTRL_L,
    TAB,
    CTRL_A,
    CTRL_K,
    CTRL_Y,
    CTRL_D,
    DEL,
    INSER,
    PERS,
    31,
    8,
    27,
    47555,
    43459,
    41155,
    42947,
    43203,
    45762,
    99315587,
    993221403,
    959601435,
    2075,
    0
  };

static int	ctrl(t_recov *recov, char *name_term)
{
  if (recov->t == CTRL_A)
    while (recov->i > 0)
      {
	if (my_cursor_move_param(name_term, "le") == FAIL)
	  return (FAIL);
	--(recov->i);
      }
  else if (recov->t == CTRL_E)
    while (recov->i < (int)strlen(recov->str))
      {
	if (my_cursor_move_param(name_term, "nd") == FAIL)
	  return (FAIL);
	++(recov->i);
      }
  else if (recov->t == CTRL_L)
    {
      if (my_clear_screen(name_term) == FAIL ||
	  manag_input() == -1 ||
	  my_write(1, recov->str, strlen(recov->str)) == -1 ||
	  my_cursor_move(strlen(INPUT) + recov->i, 0, name_term) == FAIL)
	return (FAIL);
    }
  return (OK);
}

static int	mvt(t_recov *recov, char *name_term)
{
  if (recov->t == F_HAUT)
    render_history(recov, PREVIOUS, name_term);
  else if (recov->t == F_BAS)
    render_history(recov, NEXT, name_term);
  else if (recov->t == F_GAUCHE)
    {
      if (recov->i > 0)
	{
	  if (my_cursor_move_param(name_term, "le") == FAIL)
	    return (FAIL);
	  recov->i--;
	}
    }
  else if (recov->t == F_DROITE)
    if (recov->i < (int)strlen(recov->str))
      {
	if (my_cursor_move_param(name_term, "nd") == FAIL)
	  return (FAIL);
	recov->i++;
      }
  if ((recov->t == F_HAUT || recov->t == F_BAS) && recov->str)
    if (refresh_line(recov, name_term) == FAIL)
      return (FAIL);
  return (OK);
}

int		blocked_key(int value)
{
  int		i;

  i = 0;
  while (g_key[i] && value != g_key[i])
    ++i;
  if (g_key[i] == 0)
    return (FAIL);
  return (OK);
}

int		all_touch(t_recov *recov, char *name_term, int x,
		  t_minish *min)
{
  if (touch(recov, name_term) == FAIL || mvt(recov, name_term) == FAIL ||
      ctrl(recov, name_term) == FAIL || tilde(recov, name_term) == FAIL ||
      ctrl_k_l(recov, name_term, min) == FAIL || ctrl_d(recov) == FAIL)
    return (FAIL);
  else if (blocked_key(recov->t) == FAIL &&
	   strlen(recov->str) < (MAX_SIZE_CMD - 1))
    {
      add_char_in_line(recov, recov->t);
      if (my_write(1, &(recov->str[recov->i - 1]),
		   strlen(&(recov->str[recov->i - 1]))) == -1)
	return (FAIL);
      x = strlen(recov->str);
      while (x-- > recov->i)
	if (my_cursor_move_param(name_term, "le") == FAIL)
	  return (FAIL);
    }
  if (recov->hist && recov->hist->str[0] == '\0')
    strncpy(recov->str_end, recov->str, MAX_SIZE_CMD - 1);
  return (OK);
}

int		ctrl_d(t_recov *recov)
{
  if (recov->t == CTRL_D && !recov->str[0])
    {
      my_write(1, "\n", 1);
      return (FAIL);
    }
  if (recov->t == CTRL_D)
    {
      if (my_write(1, "\n", 1) == -1)
	return (FAIL);
      return (refresh_tab(recov, recov->name_term));
    }
  return (OK);
}
