##
## Makefile for Makefile in 
## 
## Made by damien delbos
## Login   <delbos_d@epitech.net>
## 
## Started on  Mon Dec 12 18:13:54 2011 damien delbos
## Last update Fri Nov  9 21:05:46 2012 louis cauret
##

NAME	=	Bazinga

SRC	=	main.c \
		cpy_alias.c \
		refresh_tab.c \
		my_execve.c \
		unsetenv_star.c \
		add_space.c \
		my_strcpy.c \
		signal.c \
		get_return_value.c \
		check_line_conf.c \
		insert_alias.c \
		get_absolute.c \
		pre_apply.c \
		my_rev_list.c\
		unalias.c \
		alias.c \
		epur_alias.c \
		my_put_in_list.c \
		my_show_list.c \
		add_alias.c \
		check_alias.c \
		open_conf.c \
		get_nbr_words.c \
		manage_alias.c \
		manage_redirects.c \
		get_next_line.c \
		my_str_to_wordtab.c \
		minishell_2.c \
		tools.c \
		tools_2.c \
		my_cd_b.c \
		separate_cmd.c \
		builtins_b.c \
		redirection.c \
		pipe.c \
		tools_3.c \
		recover_cmd.c \
		recover_cmd_2.c \
		manage_var_env.c \
		history.c \
		sort_tab.c \
	        cmd.c   \
	        match.c \
	        path.c  \
	        blank_line.c \
		aff_tab.c \
		my_concat.c \
		hidenp.c \
		xfork.c \
		auto_complete.c \
		getenv.c \
		fmalloc.c \
		tools_4.c \
	        my_cursor_move.c \
	        my_putchar_int.c \
	        my_clear_screen.c \
	        my_kill_keyboard.c \
	        my_term_env.c \
	        my_cursor_move_param.c \
		manage_main.c \
		my_str_to_wordtab_bin.c \
		manage_env.c \
		star.c \
		my_echo_b.c \
		my_echo_2_b.c \
		my_getnbr_base.c \
		tilde.c \
		my_fcpy_env.c \
		recover_cmd_3.c \
		input.c \
		redirection_2.c \
		my_env_b.c \
		my_history_b.c \
		my_set_unset_env_b.c \
		manage_cleaning.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-I. -W -Wall

LDFLAGS	=	-L . -ltermcap

HOME	?=

$(NAME)	:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

all	:	$(NAME)

clean	:
		$(RM) *~
		$(RM) \#*#
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all
