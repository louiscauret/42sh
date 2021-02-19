/*
** my_str_to_wordtab.c for str_to_wordtab in /home/hoarau_s/42SH/42-shell/Rendu
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Wed May  2 15:26:09 2012 stephen hoarau
** Last update Sun May 20 15:53:15 2012 damien delbos
*/

#include "42.h"

static int		count_word(char *str, char x)
{
  int			i;
  int			nb_separat;

  i = 0;
  nb_separat = 0;
  while (str[i])
    {
      if (str[i] == x && str[i + 1] == x)
	{
	  nb_separat++;
	  i += 2;
	}
      i++;
    }
  return (nb_separat);
}

static int		count_len_word(char *str, int i, char x)
{
  int			len;

  len = 0;
  while (str[i] && (str[i] != x || str[i + 1] != x))
    {
      len++;
      i++;
    }
  return (len);
}

static int		attrib_i_j(int *i, int *j, char *str)
{
  *i = 0;
  *j = 0;
  if (!str)
    return (0);
  return (1);
}

char			**my_str_to_wordtab_bin(char *str, char x)
{
  char			**wordtab;
  int			nb_word;
  int			i;
  int			j;
  int			k;

  if (!attrib_i_j(&i, &j, str))
    return (NULL);
  nb_word = count_word(str, x) + 1;
  if (!(wordtab = (char **)fmalloc((nb_word + 1) * sizeof(*wordtab))))
    return (NULL);
  while (j < nb_word)
    {
      k = 0;
      if (!(wordtab[j] = fmalloc(count_len_word(str, i, x) + 1)))
	return (NULL);
      while (str[i] && (str[i] != x || str[i + 1] != x))
	wordtab[j][k++] = str[i++];
      wordtab[j] = clean_str(wordtab[j]);
      while (str[i] && str[i] == x && str[i + 1] == x)
	i += 2;
      ++j;
    }
  wordtab[j] = 0;
  return (wordtab);
}
