/*
** main.c for main in /home/delbos_d//Projets/MiniShell_1
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Tue Dec 13 16:00:00 2011 damien delbos
** Last update Wed May 23 18:18:58 2012 damien delbos
*/

#include "42.h"

int		manag_cmd(t_minish *min, int i, int find, int err)
{
  while (min->cmd[i] && min->cmd[i] != '|')
    i++;
  if (min->cmd[i])
    find = 1;
  i = 0;
  if (if_builtin(min->cmd, &err) && !find)
    {
      min->tmp = my_str_to_wordtab(min->cmd, ' ');
      if (err || (manag_fonction(min) == OK && min->exit &&
		  (min->exec_cmd = FAIL) == FAIL &&
		  (min->nb_exit = FAIL) == FAIL))
	return (min->nb_exit);
    }
  else if (min->cmd[i] && err != 1 && (err = test_pipe(min->cmd)) >= 0 &&
	   !(min->exec_cmd = 0) && err > 0)
    {
      if (!(min->tmp = my_str_to_wordtab(min->cmd, ' ')) ||
	  manag_path(min, i) == FAIL || interpret_cmd(min) == FAIL)
	return (min->nb_exit);
      my_free_minishell(min);
    }
  else if (err)
    return (min->nb_exit);
  return (min->nb_exit + 1);
}

int		manag_bin(t_minish *min, int ret)
{
  if (!(min->cmd_or = my_str_to_wordtab_bin(min->cmd, '|')))
    return (min->nb_exit);
  min->exec_cmd = FAIL;
  while (min->cmd_or && *(min->cmd_or) && min->exec_cmd == FAIL)
    {
      if ((ret = test_invalid_cmd(min->cmd_or, min->nb_exit)) >= min->nb_exit)
	return (ret);
      if (!(min->cmd_and = my_str_to_wordtab_bin(*(min->cmd_or), '&')))
	return (min->nb_exit);
      min->exec_cmd = OK;
      while (min->cmd_and && *(min->cmd_and) && min->exec_cmd == OK)
	{
	  min->cmd = *(min->cmd_and);
	  if (manag_cmd(min, 0, 0, 0) == min->nb_exit)
	    return (min->nb_exit);
	  (min->cmd_and)++;
	}
      (min->cmd_or)++;
    }
  return (min->nb_exit + 1);
}

int		main(int ac, char **av, char **env)
{
  t_minish	min;
  int		i;
  int		j;

  verif_conf_file(env);
  if (init_var_to_main(env, &min) == FAIL)
    return (min.nb_exit);
  while (ac && av)
    {
      if (recover_cmd(&min, &i, &j) == FAIL)
	return (min.nb_exit);
      while (min.list_cmd && min.list_cmd[j])
	{
	  if (!(min.list_cmd[j] = manag_star(epur_str(min.list_cmd[j]))))
	    return (min.nb_exit);
	  if (!(min.cmd = replace_to_var_env(epur_str(min.list_cmd[j++]),
					     min.env)))
	    return (min.nb_exit);
	  if (manag_bin(&min, 0) == min.nb_exit)
	    return (min.nb_exit);
	}
    }
  return (0);
}
