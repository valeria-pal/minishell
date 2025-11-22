/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_application.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:27:31 by vpaliash          #+#    #+#             */
/*   Updated: 2025/11/21 18:20:30 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	apply_redirections_to_cmd(t_command *cmd)
{
	t_redirection	*rd;

	if (!cmd)
		return (-1);
	rd = cmd->redirs;
	while (rd)
	{
		if (apply_redirect(rd) < 0)
			return (-1);
		rd = rd->next;
	}
	return (0);
}

// int	apply_all_redirections(t_command *head)
// {
// 	t_command	*cmd;

// 	if (!head)
// 		return (-1);
// 	cmd = head;
// 	while (cmd)
// 	{
// 		if (apply_redirections_to_cmd(cmd) < 0)
// 			return (-1);
// 		cmd = cmd->next;
// 	}
// 	return (0);
// }
