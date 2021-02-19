/*
** minishell_2.h for minishell_2 in /home/delbos_d//Projets/MiniShell_2
**
** Made by damien delbos
** Login   <delbos_d@epitech.net>
**
** Started on  Tue Dec 13 08:39:56 2011 damien delbos
** Last update Thu May 24 16:15:45 2012 stephen hoarau
*/

#ifndef		_42_H
# define	_42_H

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<curses.h>
#include	<term.h>
#include	<termios.h>
#include	<stdlib.h>
#include	<sys/time.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<sys/wait.h>
#include	<unistd.h>
#include	<dirent.h>
#include	<fcntl.h>
#include	<glob.h>
#include	"get_next_line.h"
#include	"my_termcap.h"

		/*MACRO MSG*/
# define	INPUT "{ShellDone}"
# define	INPUT_C "\e[\033[01;36m{ShellDone}\e[m"
# define	ERR_FORK "Error fork\n"
# define	ERR_CD "Can't change current directory.\n"
# define	ERR_STR_TO_WORDTAB "Displaying Error\n"
# define	ERR_HOME "Error: HOME environment variable not found.\n"
# define	ERR_WRITE "Error: write failed.\n"
# define	ERR_OPEN "Error: open failed.\n"
# define	ERR_READ "Error: read failed.\n"
# define	ERR_DUP2 "Error: dup2 failed.\n"
# define	ERR_CLOSE "Error: close failed.\n"
# define	ERR_PIPE "Error: pipe failed.\n"
# define	ERR_STDUP "Error: strdup failed.\n"
# define	ERR_OPEN_DIR "Error: open Directory failed.\n"
# define	ERR_READ_DIR "Error: read Directory failed.\n"
# define	ERR_CLOSE_DIR "Error: close Directory failed.\n"
# define	ERR_LSTAT "Cannot execute lstat\n"
# define	ERR_CMD_NF ": Command not found.\n"
# define	ERR_UN_VAR ": Unknown variable\n"
# define	ERR_MISS_REDIR "Missing name for redirect.\n"
# define	ERR_AMB_REDIR "Ambiguous redirection.\n"
# define	ERR_UNDEF_VAR ": Undefined variable.\n"
# define	ERR_COT "\nUnmatched \".\n"
# define	ERR_HISTORY "history : undefined parameters\n"
# define	FILE "./.my_history"
# define	ERR_MALLOC "Error: malloc failed.\n"
# define	ERR_VOID_CMD "Invalid null command.\n"
# define	MAX_SIZE_CMD 2000
# define	NEXT 1
# define	PREVIOUS 0
# define	FAIL EXIT_FAILURE

		/* SIGNALS */
# define	SIG_HUP "Hangup\n"
# define	SIG_QUIT "Quit (core dump)\n"
# define	SIG_ILL "Illegal hardware instruction (core dumped)\n"
# define	SIG_ABRT "Abort (core dump)\n"
# define	SIG_FPE	"Floating point execption (core dump)\n"
# define	SIG_KILL "Killed\n"
# define	SIG_SEGV "Segmentation fault (core dump)\n"
# define	SIG_PIPE "Broken Pipe\n"
# define	SIG_ALRM "Alarm \n"

		/*ALIAS*/
# define	CONF_FILE ".my_cnf42"
# define	ERR_ACCESS "Cannot perform Access : Permission denied\n"

		/*STRUCT*/
typedef struct  s_alias
{
  char		*memo;
  char		*cmd;
  struct s_alias*next;
  struct s_alias*prev;
}		t_alias;

typedef struct	s_hist
{
  char		str[MAX_SIZE_CMD];
  struct s_hist	*next;
  struct s_hist	*prev;
}		t_hist;

typedef struct	s_recov
{
  int		t;
  int		i;
  int		fd_hist;
  t_hist	*hist;
  char		*name_term;
  char		str_end[MAX_SIZE_CMD];
  char		str[MAX_SIZE_CMD];
}		t_recov;

typedef struct termios t_termios;

typedef struct	s_minish
{
  char		ctrl_k[MAX_SIZE_CMD];
  int		init;
  int		i;
  int		gnl;
  int		exec_cmd;
  int		fd_bin[2];
  char		**list_cmd;
  char		*cmd;
  char		*cpy_cmd;
  char		**av;
  char		**env;
  char		**path;
  char		**tmp;
  char		**cmd_and;
  char		**cmd_or;
  char		**str_bet_pip;
  char		*cd_m;
  int		exit;
  int		nb_exit;
  int		redir1;
  int		redir2;
  int		fd[2];
  int		fd_right;
  int		fd_left;
  t_termios	t_prev;
}		t_minish;

typedef struct	s_pipe
{
  int		*fd;
  int		*fd_2;
  int		redir1;
  int		redir2;
}		t_pipe;

		/*PROTOTYPES*/

t_alias		*cpy_alias(t_alias *);

		//my_execve.c
int		my_execve(t_minish *);

		//unsetenv_star.c
int		unsetenv_star(char *);

		//get_return_value.c
int		get_return_value(int);

		//signal.c
void		sign_call(int);

		//get_abosulute.c
char		*get_absolute(char *, char *occ);

		//check_line_conf.c
void		verif_conf_file(char **);
int		check_line_conf(char *);

		//get_nbr_words.c
int		get_nbr_words(char **);

		//insert_alias.c
char		*insert_alias_tmp(char *);
char		*insert_alias_conf(char *, int);

		//unalias.c
int		unalias(char *, t_alias **, t_minish *);

		//check_alias.c
void		check_alias(char *, t_alias *, t_alias *);

		//add_alias.c
char		*add_alias(char *, t_alias **);

		//epur_alias.c
char		**epur_alias(char *);

		//my_put_in_list.c
t_alias		*my_put_in_list(t_alias **, char *, char *);

		//my_rev_list.c
void		my_rev_list(t_alias **);

		//my_show_list.c
void		my_show_list(t_alias **);

		//open_conf.c
int		xopen_conf();

		//alias.c
t_alias		*alias(char *, int, t_minish *);
void		init_alias(t_alias **, int);

		//pre_apply.c
int		pre_apply(t_minish *, char *);

	      	//manage_alias.c
char		*get_alias(t_alias *, t_alias *, char *, int);
char		*clean_alias(char *);
char		*concat_tab(char **);
char		*manage_alias(char *, char **);

		//manage_main.c
int		recover_cmd(t_minish *, int *, int *);
int		init_var_to_main(char **, t_minish *);
int		if_builtin(char *, int *);
int		manag_path(t_minish *, int);

		//minishell_2.c
int 		interpret_cmd(t_minish *);
void		manag_slash(int, char *, int, char *);
char		*creat_way(char *, char *);

		//tools.c
void		my_free_minishell(t_minish *);
int		my_strlen_cd(char *);
void		my_free_tblstr(char **);
char		*xstrdup(char *);
int             count_par(char *);

		//tools_2.c
int		my_open(const char *, int, mode_t);
int		my_dup2(int, int);
int		my_close(int);
int		my_read(int, char *, int);
int		my_pipe(int *);

		//tools_3.c
int		my_strlen_tbl(char **);
int		my_write(int, char *, int);
void		add_char_in_str(int, int, char *);
char            np_char(char **, int, int, int);

		//tools_4.c
int		my_error(char *, int);
int		srch_blt(char *, char *, int *);
int		test_invalid_cmd(char **, int);

		//manage_redirects.c
int		manag_redirection(t_minish *, int *, int *, int);
int		end_redirection(t_minish *, int *, int *, int);

		//redirection.c
int		redir_right(t_minish *, int, int *);
int		redir_dbl_right(t_minish *, int, int *);
int		redir_dbl_left(t_minish *, int, int *);
int		redir_left(t_minish *, int, int *);

		//redirection_2.c
void		cut_redir(t_minish *, char *);
char            *recover_match(t_minish *, int, char *);

		//recover_cmd.c
int		touch(t_recov *, char *);
char		*manag_recovering_cmd(char **, t_recov *, struct termios,
				      t_minish *);

		//refresh_tab.c
int		refresh_tab(t_recov *, char *);

		//recover_cmd_2.c
int		refresh_line(t_recov *, char *);
void            add_char_in_line(t_recov *, char);
int		init_reco(t_recov *, char **);
int             tilde(t_recov *, char *);
int             ctrl_k_l(t_recov *, char *, t_minish *);

		//recover_cmd_3.c
int		ctrl_d(t_recov *);
int		all_touch(t_recov *, char *, int, t_minish *);
int		blocked_key(int);

		//my_str_to_wordtab.c
char		**my_str_to_wordtab(char *, char);

		//pipe.c
int		*manag_pipe(t_minish *, int);
int		test_pipe(char *);

		//separate_cmd.c
char		**separate_cmd(char *, char);

		//star.c
char            *manag_star(char *);

		//tilde.c
char            *manag_tilde(char *, char **, int, int);

		//manage_var_env.c
char		*replace_to_var_env(char *, char **);

		//history.c
int             recover_hist_to_list(t_recov *, char **);
void		render_history(t_recov *, int, char *);
int             fill_history(char *, char **);
int		my_xopen(char **);

		//auto_complete.c
char		*auto_complete(char *, char **, char **, char *);

		//sort_tab.c
char		**my_sort_tab(char **);

		//cmd.c
char		*get_files(char **, char *);
char		*cmds(char *, char **);

		//manage_env.c
char            **change_env(char **, char *, int, t_minish *);

		//match.c
int		get_slash(char *);
char		**clean_tab(char **);
char            **get_matches(char *, char *, char **);

		//path.c
int		manage_path(char *tmp[2]);

		//blank_line.c
int		blank_line(char **);

		//my_kill_keyboard.c
int		my_kill_keyboard(int, struct termios);
int		recover_struct_term(struct termios *);

		//my_getnbr_base.c
int             my_getnbr_base(char *, char *);

		//aff_tab.c
void		display_double_tab(char **);

		//my_concat.c
char            *my_concat(char *, char *);

		//hidenp.c
int		hidenp(char *, char *);

		//xfork.c
int		xfork(void);

		//getenv.c
char		*get_env(char **, char *);

		//fmalloc.c
void		*fmalloc(int);

		//my_str_to_wordtab_bin.c
char		**my_str_to_wordtab_bin(char *, char);

		//my_fcpy_env.c
char		**my_fcpy_env(char **, char *, int *, int);

		//input.c
int		manag_input(void);

		//my_strcpy.c
char		*my_strcpy(char *, char *);

		//add_space.c
char            *add_space(char *);

		//manage_cleaning.c
char		*clean_quot(char *);
char		**epur_tbl(char **);
char		*clean_str(char *);
char		*epur_str(char *);
void		clean_quote_2(char *);

		//my_set_unset_env_b.c
char		**my_unsetenv(char **, char *, t_minish *, int);
char		**my_setenv(char **, char *, t_minish *, int);

		//my_history_b.c
void		my_history(t_minish *);

		//my_env_b.c
int		my_env(char **, char *, int *, int);

		//builtins_b.c
int		manag_fonction(t_minish *);

		//my_cd_b.c
char		**my_cd(char *, char **, t_minish *);

		//my_echo_b.c
void		my_echo(char *, t_minish *);

		//my_echo_2_b.c
char		*manag_backslash(char *, int *);

#endif
