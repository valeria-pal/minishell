/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_application.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:27:31 by vpaliash          #+#    #+#             */
/*   Updated: 2025/11/23 11:48:47 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

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
