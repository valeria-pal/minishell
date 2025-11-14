/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1cm_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 20:47:34 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/14 20:53:54 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

static int	process_command_loop(t_command *cmd, t_token **tok_ptr,
		t_bash *bash_struct)
{
	int	i;

	i = 0;
	while (*tok_ptr && (*tok_ptr)->type != PIPE && (*tok_ptr)->type != EOL)
	{
		if ((*tok_ptr)->type == WORD)
		{
			cmd->argv[i] = normalize_word((*tok_ptr)->value, bash_struct);
			if (!cmd->argv[i])
				return (0);
			i++;
			*tok_ptr = (*tok_ptr)->next;
		}
		else if (!add_redirection(cmd, tok_ptr))
			return (0);
	}
	if (cmd->argv)
		cmd->argv[i] = NULL;
	return (1);
}

t_command	*parse_one_command(t_token **tok_ptr, t_bash *bash_struct)
{
	t_command	*cmd;

	cmd = cmd_new();
	if (!cmd)
		return (NULL);
	if (count_args_until_pipe(*tok_ptr) > 0)
	{
		cmd->argv = malloc(sizeof(char *) * (count_args_until_pipe(*tok_ptr)
					+ 1));
		if (!cmd->argv)
			return (free(cmd), NULL);
	}
	if (!process_command_loop(cmd, tok_ptr, bash_struct))
		return (free_commands(cmd), NULL);
	return (cmd);
}
