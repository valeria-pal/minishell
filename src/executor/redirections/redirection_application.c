/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_application.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:27:31 by vpaliash          #+#    #+#             */
/*   Updated: 2025/11/20 19:15:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	apply_redirections_to_cmd( t_command *cmd)
{
	t_redirection	*rd;

	if (!cmd )
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
