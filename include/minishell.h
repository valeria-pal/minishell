#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>

# include <stdio.h>
# include <stdlib.h>

#include <signal.h>
#include <unistd.h>

extern volatile sig_atomic_t g_sig;

void	prompt(void);
void	signal_handler(int signum);

#endif