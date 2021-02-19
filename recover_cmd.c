/*
** main.c for main in /home/delbos_d//Test/PROMPT
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Wed Apr  4 20:44:51 2012 damien delbos
** Last update Thu May 24 15:31:09 2012 stephen hoarau
*/

#include "42.h"

int		touch(t_recov *recov, char *name_term)
{
  int		x;

  if (recov->t == BCKSPACE)
    {
      if  (strlen(recov->str) && recov->i > 0)
	{
	  if (my_cursor_move_param(name_term, "le") == FAIL)
	    return (FAIL);
	  my_strcpy(&(recov->str[recov->i - 1]), &(recov->str[recov->i]));
	  recov->i--;
	  if (my_write(1, &(recov->str[recov->i]),
		       strlen(&(recov->str[recov->i]))) == -1 ||
	      my_write(1, " ", 1) == -1)
	    return (FAIL);
	  x = strlen(&(recov->str[recov->i])) + 1;
	  while (x > 0)
	    {
	      x--;
	      if (my_cursor_move_param(name_term, "le") == FAIL)
		return (FAIL);
	    }
	}
    }
  return (OK);
}

char		*manag_recovering_cmd(char **env, t_recov *recov,
				      struct termios t_prev, t_minish *min)
{
  char		*str;

  if (!(recov->name_term = my_term_env(env, 2)) || min->gnl == FAIL)
    return (get_next_line(0));
  if (my_kill_keyboard(1, t_prev) == FAIL || init_reco(recov, min->env) == FAIL)
    return (NULL);
  while (recov->t != ENTREE || my_write(1, "\n", 1))
    {
      recov->t = 0;
      if (my_read(0, (char *)&(recov->t), 4) == -1)
	return (NULL);
      if (recov->t == TAB)
	{
	  if (my_write(1, "\n", 1) == -1 ||
	      !(str = auto_complete(recov->str, env, NULL, 0)) ||
	      my_write(1, "\r", 1) == -1)
	    return (NULL);
	  strncpy(recov->str, str, MAX_SIZE_CMD - 1);
	  if (refresh_tab(recov, recov->name_term) == FAIL)
	    return (NULL);
	}
      else if (all_touch(recov, recov->name_term, 0, min) == FAIL)
	return (NULL);
    }
  return (xstrdup(recov->str));
}
