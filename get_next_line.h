/*
** get_next_line.h for get_next_line in /home/delbos_d//Projets/Get_next_line
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Tue Nov 22 11:08:27 2011 damien delbos
** Last update Thu May  3 08:50:28 2012 luc terracher
*/

#ifndef		_GET_NEXT_LINE_H
# define	_GET_NEXT_LINE_H

		/*STRUCTURE*/
typedef		struct	s_gnl
{
  char          *buf;
  int           size_cpy;
  int           size_buf;
  int           i;
  int           count;
  int           j;
  int		bef_init;
  int		pos;
  int		x;
  int		y;
}		t_gnl;

		/*PROTOTYPE*/
char		*get_next_line(const int fd);

		/*MACRO*/
# define	SIZE_STR_READ 10000
# define	SIZE_MAX_BUFFER 10000

#endif
