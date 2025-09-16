/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaliash <vpaliash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:23:56 by vpaliash          #+#    #+#             */
/*   Updated: 2025/09/16 10:23:59 by vpaliash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	prompt(void)
{
	char	*line_read;

	while (1)
	{
		line_read = readline("minishell$ ");
		if (g_sig == SIGINT)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_sig = 0;
			free(line_read);
			continue ;
		}
		if (!line_read)
			break ;
		if (*line_read)
			add_history(line_read);
		if (line_read)
		{
			free(line_read);
			line_read = NULL;
		}
		while (1) // test loop to check signal handling
		{
			if (g_sig == SIGINT)
			{
				g_sig = 0;
				break ;
			}
			write(1, "a/n", 2);
		}
	}
}
