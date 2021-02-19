/*
** signal.c for 42sh in /home/hoarau_s/42SH/42-shell/Rendu
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Thu May 17 13:19:07 2012 stephen hoarau
** Last update Sun May 20 15:39:13 2012 stephen hoarau
*/

#include "42.h"

void		sign_call(int sign)
{
  if (sign == SIGINT || sign == SIGQUIT)
    my_write(1, "\n", 1);
  manag_input();
}
