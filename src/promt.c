#include "../include/minishell.h"

void	promt()
{
	char *line = readline("minishell $");
	printf("%s", line);
	free(line);
}