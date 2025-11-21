/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:31:36 by marvin            #+#    #+#             */
/*   Updated: 2025/11/20 17:31:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	count_cmds(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	close_pipes(int pipe_fds[][2], int pipe_count)
{
	int i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
	}
}


int	(*create_pipes(t_command *cmd))[2]
{
	int	(*pipes)[2];
	int	pipe_count;
	int	i;

	i = 0;
	pipe_count = count_cmds(cmd) - 1;
	if (pipe_count <= 0)
		return (NULL);
	pipes = malloc(pipe_count * sizeof(int[2]));
	if (!pipes)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (i < pipe_count)
	{
		pipe_error_check(pipes, i);
		i++;
	}
	return (pipes);
}

pid_t	*allocate_pids(int cmd_count, int (*pipes)[2])
{
	pid_t	*pids;
	int pipe_count;

	pipe_count = cmd_count - 1;
	pids = malloc(cmd_count * sizeof(pid_t));
	if (!pids)
	{
		perror("malloc");
		if (pipes)
		{
			close_pipes(pipes, pipe_count);
			free(pipes);
		}
		exit(EXIT_FAILURE);
	}
	return (pids);
}
