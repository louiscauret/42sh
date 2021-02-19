/*
** my_echo_2_b.c for my_echo_2_b in /home/delbos_d//Projets/42-SH/Rendu
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Thu May 10 17:19:14 2012 damien delbos
** Last update Wed May 23 20:49:13 2012 damien delbos
*/

#include "42.h"

static char	*manag_hexa(char *cmd, char *c)
{
  char		hex_oct[4];

  hex_oct[0] = *(cmd + 1);
  hex_oct[1] = 0;
  if ((*(cmd + 2) >= '0' && *(cmd + 2) <= '9') ||
      (*(cmd + 2) >= 'A' && *(cmd + 2) <= 'Z'))
    {
      hex_oct[1] = *(cmd + 2);
      hex_oct[2] = 0;
    }
  *c = my_getnbr_base(hex_oct, "0123456789ABCDEF");
  cmd += strlen(hex_oct) + 1;
  return (cmd);
}

static char	*manag_oct(char *cmd, char *c)
{
  char		hex_oct[4];

  hex_oct[0] = *(cmd + 1);
  hex_oct[1] = 0;
  if (*(cmd + 2) >= '0' && *(cmd + 2) <= '7')
    {
      hex_oct[1] = *(cmd + 2);
      hex_oct[2] = 0;
    }
  if (*(cmd + 2) && *(cmd + 3) >= '0' && *(cmd + 3) <= '7')
    {
      hex_oct[2] = *(cmd + 3);
      hex_oct[3] = 0;
    }
  *c = my_getnbr_base(hex_oct, "01234567");
  cmd += strlen(hex_oct) + 1;
  return (cmd);
}

char		*manag_spec_char(char *cmd, char *c, int *ret)
{
  char		charact[10];
  char		num[10];
  int		i;

  i = 0;
  *ret = 0;
  strcpy(charact, "\\abefnrtv");
  strcpy(num, "\\\a\b\e\f\n\r\t\v");
  while (i < 10 && charact[i] != *cmd)
    ++i;
  if (i < 10)
    {
      *c = num[i];
      cmd++;
      *ret = 1;
    }
  return (cmd);
}

char		*manag_backslash(char *cmd, int *backn)
{
  char		c;
  int		ret;

  if ((cmd = manag_spec_char(cmd, &c, &ret)) && ret)
    ret = 1;
  else if (*cmd == 'x' && ((*(cmd + 1) >= '0' && *(cmd + 1) <= '9') ||
                           (*(cmd + 1) >= 'A' && *(cmd + 1) <= 'Z')))
    cmd = manag_hexa(cmd, &c);
  else if (*cmd == '0' && *(cmd + 1) >= '0' && *(cmd + 1) <= '7')
    cmd = manag_oct(cmd, &c);
  else if (*cmd == 'c' && !(*cmd = 0) && !(*backn = 0))
    return (cmd);
  else
    {
      c = *cmd;
      cmd++;
    }
  if (my_write(1, &c, 1) == -1)
    return (NULL);
  if (c == 'c')
    if (my_write(1, &c, 1) == -1)
      return (NULL);
  return (cmd);
}
