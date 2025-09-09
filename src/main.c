
#include "../include/minishell.h"

int	main(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	prompt();


	return (0);
}
