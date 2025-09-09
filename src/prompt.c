#include "../include/minishell.h"

void	prompt(void)
{
	char	*line_read;

	while (1)
	{
		line_read = readline("minishell$ ");
		if (!line_read)
			break;
		if (g_sig == SIGINT)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_sig = 0;
			free(line_read);
			continue ;
		}
		if (*line_read && line_read)
			add_history(line_read);
		if (line_read)
		{
			free(line_read);
			line_read = NULL;
		}
	}
}
