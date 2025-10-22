/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_appplication.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaliash <vpaliash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:27:31 by vpaliash          #+#    #+#             */
/*   Updated: 2025/10/22 10:33:42 by vpaliash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	apply_redirections_to_cmd(const t_command *cmd)
{
	const t_redirection	*rd;

	if (!cmd || !cmd->redirs)
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

int	apply_all_redirections(t_command *head)
{
	if (!head)
		return (-1);
	t_command *cmd;
	cmd = head;
	while (cmd)
	{
		if (apply_redirections_to_cmd < 0)
			return (-1);
		cmd = cmd->next;
	}
	return (0);
}