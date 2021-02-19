/*
** epur_alias.c for 42sh in /home/hoarau_s/42SH/42-shell/Stephen/alias
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Thu May 10 12:29:12 2012 stephen hoarau
** Last update Wed May 23 18:42:44 2012 damien delbos
*/

#include "42.h"

char		**epur_alias(char *buffer)
{
  int		len;
  int		i;
  int		count;
  char		**tbl;

  i = 0;
  if (!(tbl = fmalloc(2 * sizeof(char *))))
    return (NULL);
  while (buffer[0] == ' ' || buffer[0] == '\t')
    buffer += 1;
  while (buffer[i] != '=')
    i++;
  count = i;
  while (buffer[i] == '=')
    i++;
  tbl[0] = strndup(buffer, count);
  if (tbl[0] == NULL)
    return (NULL);
  tbl[1] = xstrdup(buffer + i);
  len = strlen(tbl[1]);
  tbl[1][len - 1] = '\0';
  tbl[1] += 1;
  return (tbl);
}
