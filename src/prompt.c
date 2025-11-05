/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:15:46 by vpaliash          #+#    #+#             */
/*   Updated: 2025/11/03 16:54:02 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

void	prompt(char **envp)
{
	char	*line_read;

	while (1)
	{
		line_read = readline("minishell$ ");
		if (!line_read)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*line_read)
			add_history(line_read);
		tokenize_output(line_read, envp);
		if (line_read)
		{
			free(line_read);
			line_read = NULL;
		}
	}
	rl_clear_history();
}
