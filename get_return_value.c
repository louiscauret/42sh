/*
** get_return_value.c for 42sh in /home/hoarau_s/42SH/42-shell/Rendu
**
** Made by stephen hoarau
** Login   <hoarau_s@epitech.net>
**
** Started on  Thu May 17 14:13:56 2012 stephen hoarau
** Last update Sun May 20 16:20:58 2012 luc terracher
*/

#include "42.h"

static const int	 g_signals[] =
{
  SIGHUP,
  SIGQUIT,
  SIGILL,
  SIGABRT,
  SIGFPE,
  SIGKILL,
  SIGSEGV,
  SIGPIPE,
  SIGALRM,
  0
};

static void		free_tab(char **tbl)
{
  int			i;

  i = 0;
  while (i <= 8)
    free(tbl[i++]);
  free(tbl);
}

static char		**init_tab(char **err_sign)
{
  err_sign = fmalloc(9 * sizeof(char *));
  if (err_sign == NULL)
    return (NULL);
  err_sign[0] = xstrdup(SIG_HUP);
  err_sign[1] = xstrdup(SIG_QUIT);
  err_sign[2] = xstrdup(SIG_ILL);
  err_sign[3] = xstrdup(SIG_ABRT);
  err_sign[4] = xstrdup(SIG_FPE);
  err_sign[5] = xstrdup(SIG_KILL);
  err_sign[6] = xstrdup(SIG_SEGV);
  err_sign[7] = xstrdup(SIG_PIPE);
  err_sign[8] = xstrdup(SIG_ALRM);
  return (err_sign);
}

int			get_signal_value(int signal)
{
  int			i;
  char			**err_sign;

  i = 0;
  err_sign = 0;
  err_sign = init_tab(err_sign);
  if (err_sign == NULL)
    return (FAIL);
  while (g_signals[i] != 0)
    {
      if (g_signals[i] == signal)
	if (my_error(err_sign[i], 1) == -1)
	  return (FAIL);
      i++;
    }
  free_tab(err_sign);
  return (FAIL);
}

int			get_return_value(int status)
{
  if (WIFEXITED(status))
    {
      if (WEXITSTATUS(status) == 0)
	return (OK);
      else
	return (FAIL);
    }
  else if (WIFSIGNALED(status))
    return (get_signal_value(WTERMSIG(status)));
  return (FAIL);
}
