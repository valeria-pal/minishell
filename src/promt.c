#include "../include/minishell.h"

void	promt()
{
	char *line_read = readline("minishell$ ");
	printf("%s", line_read);

	if(!line_read)
	exit(0);// or use signal SIGINT

	if(*line && line_read)
	add_history(line_read);

	if(line_read)
	{
	free(line_read);
	line_read = NULL;
	}
}