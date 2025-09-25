/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:15:46 by vpaliash          #+#    #+#             */
/*   Updated: 2025/09/25 20:56:29 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

void	prompt(void)
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
		tokenize_output(line_read);
		if (line_read)
		{
			free(line_read);
			line_read = NULL;
		}
		// while (1) // test loop to check ctrl/c handling, you can remove it later
		// {
			// if (g_sig == SIGINT)
			// {
			// 	g_sig = 0;
			// 	break ;
			// }
			//write(1, "a/n", 2);
			//usleep(100000);
		//}
	}
	rl_clear_history();
}
