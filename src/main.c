/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaliash <vpaliash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:13:18 by vpaliash          #+#    #+#             */
/*   Updated: 2025/09/25 17:44:01 by vpaliash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <stdio.h>

/* int	main(void)
{
	set_termios();
	setup_signals();
	prompt();
	return (0);
} */

// test for executor for raw_data_

int	main(int argc, char **argv, char *const envp[])
{
	(void)argc;
	(void)argv;
	t_cmd *cmd;
	int status;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (1);

	cmd->next = NULL;
	cmd->args = malloc(2 * sizeof(char *));
	cmd->args[0] = strdup("fohfowh");
	cmd->args[1] = NULL;
	status = execute(cmd, envp);
	if (status == 0)
		printf("success\n");
	else
		printf("command failed: %d\n", status);
	free(cmd->args[0]);
	free(cmd->args);
	free(cmd);
	return (0);
}