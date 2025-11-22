/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:34:07 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/15 12:04:16 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_commands(t_command *cmd)
{
	int				c;
	t_redirection	*r;
	int				i;

	c = 0;
	while (cmd)
	{
		printf("Command %d:\n", c++);
		printf("  argv: ");
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
			{
				printf("%s\n", cmd->argv[i]);
				i++;
			}
		}
		printf("\n");
		printf("  redirs: ");
		r = cmd->redirs;
		while (r)
		{
			printf("%d, %s ", r->type, r->filename);
			r = r->next;
		}
		printf("\n");
		cmd = cmd->next;
	}
}
