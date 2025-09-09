
#include "../include/minishell.h"

volatile sig_atomic_t g_sig = 0;

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sig = SIGINT;
		write(2, "\n", 1);
		
	}
	else if (signum == SIGQUIT)
	{
		(void)g_sig;
	}
}
