/*
** manage_cleaning.c for manage_cleaning in /home/delbos_d//Projets/42-SH/svn_42sh/Rattrapage
** 
** Made by damien delbos
** Login   <delbos_d@epitech.net>
** 
** Started on  Wed May 23 19:22:36 2012 damien delbos
** Last update Wed May 23 21:09:39 2012 damien delbos
*/

#include "42.h"

char	*clean_quot(char *str)
{
  if (!str)
    return (NULL);
  while ((str[0] == '"' || str[0] == '\'') &&
	 (str[1] == '"' || str[1] == '\''))
    my_strcpy(str, &str[2]);
  return (str);
}

char	**epur_tbl(char **tbl)
{
  int	i;
  int	j;
  int	p;

  if (!tbl)
    return (NULL);
  i = 0;
  while (tbl[i])
    clean_quot(tbl[i++]);
  i = 0;
  while (tbl[i])
    {
      p = i;
      while (tbl[p] && !tbl[p][0])
        {
          j = p;
          while (tbl[j])
            {
              tbl[j] = tbl[j + 1];
              ++j;
            }
        }
      ++i;
    }
  return (tbl);
}

char	*clean_str(char *str)
{
  int	i;

  while (*str == ' ' || *str == '\t')
    my_strcpy(str, &str[1]);
  i = strlen(str) - 1;
  if (i < 0)
    i = 0;
  while (str[i] == ' ' || str[i] == '\t')
    str[i--] = 0;
  return (str);
}

char	*epur_str(char *str)
{
  char	*cmd;

  if (!str)
    {
      if ((cmd = fmalloc(1)) == NULL)
        return (NULL);
      return (cmd);
    }
  while (*str == ' ' || *str == '\t')
    my_strcpy(str, &str[1]);
  return (str);
}

void	clean_quote_2(char *cmd)
{
  while (*cmd == '\'' || *cmd == '"')
    my_strcpy(&cmd[0], &cmd[1]);
  while (cmd[strlen(cmd) - 1] == '\'' || cmd[strlen(cmd) - 1] == '"')
    cmd[strlen(cmd) - 1] = 0;
}
