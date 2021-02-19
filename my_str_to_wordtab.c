/*
** my_str_to_wordtab.c for str_to_wordtab in /home/hoarau_s/42SH/42-shell/Rendu
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Wed May  2 15:26:09 2012 stephen hoarau
** Last update Sun May 20 14:02:20 2012 stephen hoarau
*/

#include "42.h"

static int              count_word(char *str, char x, int i, int nb)
{
  char                   par;

  par = 0;
  if (count_par(str) == 0)
    return (0);
  while (str[i])
    {
      while (str[i] == x)
        i++;
      if ((str[i] == '"' || str[i] == '\'') && par == str[i] && ++nb)
        {
	  while (str[i] && str[i] != par)
	    ++i;
	  if (str[i])
	    i++;
	}
      if (str[i] && str[i] != x && ++nb)
	while (str[i] && str[i] != x)
	  ++i;
    }
  if ((par % 2) != 0)
    return (-1);
  return (nb);
}

static int		count_len_word(char *str, int i, char x)
{
  int			len;
  int			par;

  len = 0;
  par = 0;
  while (str[i] && str[i] != x && par < 2)
    {
      if ((str[i] == '"' || str[i] == '\'') && ++par)
	while ((par % 2) != 0 && str[i])
	  {
	    ++i;
	    ++len;
            if ((str[i] == '"' || str[i] == '\'') && ++i)
              ++par;
          }
      len++;
      i++;
    }
  return (len);
}

static int		attrib_i_j(int *i, int *j, char *str, int *par)
{
  *i = 0;
  *j = 0;
  *par = 0;
  if (!str)
    return (0);
  return (1);
}

static char		**word_void(int nb)
{
  char			**word;

  if (nb == -1)
    if (write(2, ERR_COT, strlen(ERR_COT)) == -1)
      return (NULL);
  if (!(word = fmalloc(2 * sizeof(*word))))
    return (NULL);
  word[1] = NULL;
  if (!(word[0] = fmalloc(1)))
    return (NULL);
  word[0][0] = 0;
  return (word);
}

char			**my_str_to_wordtab(char *str, char x)
{
  char			**wordtab;
  int			nb_word;
  int			i;
  int			j;
  int			k;
  int			par;

  if (!attrib_i_j(&i, &j, str, &par))
    return (NULL);
  if ((nb_word = count_word(str, x, 0, 0) + 1) == 1 || nb_word == -1)
    return (word_void(nb_word));
  if (!(wordtab = fmalloc((nb_word + 1) * sizeof(*wordtab))) ||
      (wordtab[nb_word] = 0))
    return (NULL);
  while (str[i])
    {
      k = 0;
      if (!(wordtab[j] = fmalloc((k = count_len_word(str, i, x)) + 1)))
	return (NULL);
      strncpy(wordtab[j++], &str[i], k);
      i += k;
      while (str[i] && str[i] == x)
	++i;
    }
  return (wordtab);
}
