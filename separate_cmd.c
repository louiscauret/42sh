/*
** separate_cmd.c for separate_cmd in /home/delbos_d//Projets/My_str_to_wordtab
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Thu Feb 23 20:48:57 2012 damien delbos
** Last update Thu May 24 01:24:09 2012 damien delbos
*/

#include "42.h"

static int	nb_char(char *str, char char_ban)
{
  int		i;
  int		guill;

  i = 0;
  guill = 0;
  while (str[i] && (str[i] != char_ban || (guill % 2) != 0))
    {
      if (str[i] == '"' || str[i] == '\'')
	guill++;
      i++;
    }
  return (i);
}

static int	count_word(char *str, char char_ban)
{
  int		i;
  int		nb;
  int		guill;

  i = 0;
  nb = 0;
  guill = 0;
  while (str[i])
    {
      while (str[i] && (str[i] != char_ban || (guill % 2) != 0))
	{
	  if (str[i] == '"' || str[i] == '\'')
	    guill++;
	  i++;
	}
      if (str[i] == char_ban)
	nb++;
      if (str[i])
	i++;
    }
  if ((guill % 2) != 0)
    if (my_error(ERR_COT, 1) == -1)
      return (-1);
  return (nb + 1);
}

static char	*change(char *str, char *dest, int nb)
{
  int		i;

  i = 0;
  strncpy(dest, str, nb);
  while (i < nb)
    {
      str++;
      i++;
    }
  return (str);
}

char		**separate_cmd(char *str, char c)
{
  char		**word;
  int		nb;
  char		*cpy;
  int		i;

  i = 0;
  if ((nb = count_word(str, c)) == -1)
    return (NULL);
  if (!(word = fmalloc((nb + 1) * sizeof(*word))))
    return (NULL);
  while (i < nb)
    {
      if (i != 0)
	while (*str == c)
	  str++;
      if (!(word[i] = fmalloc(nb_char(str, c) + 1)))
	return (NULL);
      str = change(str, word[i], nb_char(str, c));
      cpy = clean_str(word[i]);
      my_strcpy(word[i], cpy);
      i++;
    }
  word[i] = NULL;
  return (word);
}
