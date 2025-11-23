/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 00:24:46 by marvin            #+#    #+#             */
/*   Updated: 2025/11/23 19:44:34 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../include/minishell.h"

void	pipe_error_check(int pipe_fds[][2], int i)
{
	if (pipe(pipe_fds[i]) == -1)
	{
		perror("pipe");
		close_pipes(pipe_fds, i);
		free(pipe_fds);
		exit(EXIT_FAILURE);
	}
}

void	errno_checker(void)
{
	if (errno == EACCES)
		exit(126);
	else if (errno == ENOENT)
		exit(127);
	else
		exit(1);
}

void	check_fork_error(pid_t pid)
{
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return ;
}

void	handle_redirections_or_exit(t_command *cmd, char *path)
{
	if (apply_redirections_to_cmd(cmd) < 0)
	{
		if (path)
			free(path);
		exit(1);
	}
}
