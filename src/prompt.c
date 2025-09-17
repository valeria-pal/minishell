/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaliash <vpaliash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:15:46 by vpaliash          #+#    #+#             */
/*   Updated: 2025/09/17 14:09:49 by vpaliash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	}
	rl_clear_history();
}
