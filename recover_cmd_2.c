/*
** recover_cmd_2.c for recover_cmd_2 in /home/delbos_d//Projets/42-SH/Rendu
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Thu Apr  5 10:42:30 2012 damien delbos
** Last update Thu May 24 15:31:39 2012 stephen hoarau
*/

#include "42.h"

int		ctrl_k_l(t_recov *recov, char *name_term, t_minish *min)
{
  char		cpy[MAX_SIZE_CMD];
  int		i;

  if (recov->t == CTRL_K)
    {
      strcpy(min->ctrl_k, &(recov->str[recov->i]));
      i = strlen(min->ctrl_k);
      recov->i += i;
      while (i--)
	if (my_write(1, " ", 1) == -1)
	  return (FAIL);
      recov->str[recov->i - strlen(min->ctrl_k)] = 0;
      return (refresh_line(recov, name_term));
    }
  else if (recov->t == CTRL_Y &&
	   strlen(recov->str) + strlen(min->ctrl_k) < MAX_SIZE_CMD)
    {
      strcpy(cpy, &(recov->str[recov->i]));
      strcpy(&(recov->str[recov->i]), min->ctrl_k);
      strcpy(&(recov->str[strlen(recov->str)]), cpy);
      return (refresh_line(recov, name_term));
    }
  return (OK);
}

int		tilde(t_recov *recov, char *name_term)
{
  int		x;

  x = 0;
  if ((recov->t == INSER || recov->t == DEL) &&
      strlen(recov->str) < (MAX_SIZE_CMD - 1))
    {
      add_char_in_line(recov, '~');
      if (my_write(1, &(recov->str[recov->i - 1]),
                   strlen(&(recov->str[recov->i - 1]))) == -1)
        return (FAIL);
      x = strlen(recov->str);
      while (x > recov->i)
        {
          x--;
          if (my_cursor_move_param(name_term, "le") == FAIL)
            return (FAIL);
        }
    }
  return (OK);
}

int		refresh_line(t_recov *recov, char *name_term)
{
  while (recov->i < (int)strlen(recov->str))
    {
      ++(recov->i);
      if (my_cursor_move_param(name_term, "nd") == FAIL)
	return (FAIL);
    }
  recov->i += strlen(INPUT);
  while (recov->i > 0)
    {
      (recov->i)--;
      if (my_cursor_move_param(name_term, "le") == FAIL || my_write(1, " ", 1)
	  || my_cursor_move_param(name_term, "le") == FAIL)
	return (FAIL);
    }
  if (manag_input() == -1 ||
      my_write(1, recov->str, strlen(recov->str)) == -1)
    return (FAIL);
  recov->i = strlen(recov->str);
  return (OK);
}

void		add_char_in_line(t_recov *recov, char c)
{
  char		cpy[MAX_SIZE_CMD];

  strcpy(cpy, recov->str);
  recov->str[recov->i++] = c;
  strcpy(&(recov->str[recov->i]), &cpy[recov->i - 1]);
}

int		init_reco(t_recov *recov, char **env)
{
  recov->t = 0;
  recov->i = 0;
  recov->str[0] = 0;
  recov->str_end[0] = 0;
  if (recover_hist_to_list(recov, env) == FAIL)
    return (FAIL);
  return (OK);
}
