/*
** my_strcpy.c for strcpy in /home/serra_r//42-shell/Rendu
** 
** Made by romain serra
** Login   <serra_r@epitech.net>
** 
** Started on  Sun May 20 16:48:12 2012 romain serra
** Last update Sun May 20 16:48:42 2012 romain serra
*/

char	*my_strcpy(char *dest, char *src)
{
  int	i;

  i = 0;
  while (src[i])
    {
      dest[i] = src[i];
      i++;
    }
  dest[i] = '\0';
  return (dest);
}
