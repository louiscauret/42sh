/*
** my_termcap.h for my_termcap in /home/delbos_d//Library/Libtermcap
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Tue Jan 17 22:42:26 2012 damien delbos
** Last update Sun May 20 16:19:33 2012 damien delbos
*/

#ifndef		_MY_TERMCAP_H
# define	_MY_TERMCAP_H

int		my_putchar_int(int);
void		my_soul_mod(int, char *);
void		my_inv_mod(int, char *);
int		my_clear_screen(char *);
int		my_cursor_move(int, int, char *);
char		*my_term_env(char **, int);
int		my_cursor_move_param(char *, char *);

	/* MACROS MSG */
# define	M_ERRNAME "Error: invalid name.\n"
# define	M_ERRDTB "Error: databases not found.\n"
# define	M_TCGATTR "Error: tcgetattr failed.\n"
# define	M_TCSATTR "Error: tcsetattr failed.\n"
# define	M_ERRTGENT "Error: tgetent failed.\n"
# define	M_ERRTGSRT "Error: tgetstr failed.\n"
# define	M_ERRVARENV "Error: TERM environment variable not found.\n"

	/* MACROS */
# define	F_DROITE 4414235
# define	F_GAUCHE 4479771
# define	ENTREE 10
# define	F_HAUT 4283163
# define	F_BAS 4348699
# define	DEL 2117294875
# define	BCKSPACE 127
# define	TAB 9
# define	CTRL_L 12
# define	CTRL_D 4
# define	CTRL_A 1
# define	CTRL_E 5
# define	CTRL_K 11
# define	CTRL_Y 25
# define	INSER 2117229339
# define	PERS 47555

#endif
