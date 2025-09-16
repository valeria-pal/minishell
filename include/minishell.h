#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>

# include <stdio.h>
# include <stdlib.h>

#include <signal.h>
#include <termios.h>
#include <unistd.h>

extern volatile sig_atomic_t g_sig;

void	prompt(void);
void	signal_handler(int signum);
void setup_signals(void);
void set_termios(void);
void	*ft_memset(void *s, int value, size_t n);

#endif