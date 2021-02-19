/*
** my_echo_b.c for my_echo_b in /home/delbos_d//Projets/42-SH/Rendu
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Thu May 10 09:43:53 2012 damien delbos
** Last update Wed May 23 20:48:20 2012 damien delbos
*/

#include "42.h"

static char	*manag_opt(char *str, int *backn, int *backe, char *cmd)
{
  cmd = str;
  while (*cmd == '-')
    {
      cmd++;
      while (*cmd && *cmd != ' ' && *cmd != '\t')
	{
	  if (*cmd == 'n')
	    *backn = 0;
	  else if (*cmd == 'e')
	    *backe = 1;
	  else if (*cmd == 'E')
	    *backe = 0;
	  else
	    {
	      *backe = 0;
	      *backn = 1;
	      return (str);
	    }
	  ++cmd;
	}
      while (*cmd == ' ' || *cmd == '\t')
	cmd++;
    }
  return (cmd);
}

static int	displaying_echo(char *cmd, int backn, int backe)
{
  while (*cmd)
    {
      if (backe && *cmd == '\\')
	{
	  ++cmd;
	  if (!(cmd = manag_backslash(cmd, &backn)))
	    return (-1);
	}
      else if (!backe && *cmd == '\\')
	{
	  my_write(1, cmd, 1);
	  ++cmd;
	}
      else
	{
	  if (my_write(1, cmd, 1) == -1)
	    return (-1);
	  ++cmd;
	}
    }
  if (backn)
    if (my_write(1, "\n", 1) == -1)
      return (-1);
  return (0);
}

char		*manage_double_quotes(char *cmd)
{
  int		i;
  char		**tbl;

  i = 0;
  if ((tbl = my_str_to_wordtab(cmd, ' ')) == NULL)
    return (NULL);
  while (tbl[i])
    {
      if (tbl[i][0] != '-')
	{
	  if (tbl[i][0] == '"' || tbl[i][0] == '\'')
	    tbl[i] += 1;
	  if (tbl[i][strlen(tbl[i]) - 1] == '"' ||
	      tbl[i][strlen(tbl[i]) - 1] == '\'')
	    tbl[i][strlen(tbl[i]) - 1] = '\0';
	}
      i++;
    }
  return (concat_tab(tbl));
}

void		my_echo(char *cmd, t_minish *min)
{
  int		backn;
  int		backe;

  cmd = clean_str(cmd);
  backn = 1;
  backe = 0;
  cmd = manage_double_quotes(cmd);
  cmd = manag_opt(cmd, &backn, &backe, NULL);
  if (displaying_echo(cmd, backn, backe) == -1 && (min->exit = 1))
    return ;
  return ;
}
