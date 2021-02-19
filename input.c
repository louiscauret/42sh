/*
** input_test.c for input in /home/serra_r//42-shell/Rendu
** 
** Made by romain serra
** Login   <serra_r@epitech.net>
** 
** Started on  Wed May 16 12:20:44 2012 romain serra
** Last update Sun May 20 15:42:42 2012 louis cauret
*/

#include "42.h"

int		manag_input(void)
{
  return (my_write(1, INPUT_C, strlen(INPUT_C)));
}
