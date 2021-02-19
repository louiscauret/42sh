/*
** pre_apply.c for 42sh in /home/hoarau_s/42SH/42-shell/Rendu
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Mon May 14 14:49:23 2012 stephen hoarau
** Last update Wed May 23 20:52:01 2012 damien delbos
*/

#include "42.h"

int		pre_apply(t_minish *min, char *cmd_cpy)
{
  if (!(min->cmd = manag_tilde(cmd_cpy, min->env, 0, 0)) ||
      !(min->cmd = clean_str(min->cmd)) ||
      !(min->cmd = add_space(min->cmd)) ||
      !(min->cmd = manage_alias(min->cmd, min->env)) ||
      !(min->list_cmd = epur_tbl(separate_cmd(min->cmd, ';'))))
    return (FAIL);
  return (OK);
}
