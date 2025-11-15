/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:21:54 by vpaliash          #+#    #+#             */
/*   Updated: 2025/11/15 12:02:47 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_pipes(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd && cmd->next)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int	(*create_pipe(int cmd_count))[2]
{
	int	(*pipe_fds)[2];
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = cmd_count - 1;
	if (pipe_count <= 0)
		return (NULL);
	pipe_fds = malloc((pipe_count - 1) * sizeof(int [2]));
	if (!pipe_fds)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (i < pipe_count)
	{
		if (pipe(pipe_fds[i]) == -1)
		{
			perror("pipe");
			free(pipe_fds[i]);
			free(pipe_fds);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipe_fds);
}

void	launch_command(t_command *cmd, int i, int pipe_fds[][2], int cmd_count)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (cmd->next)
		{
			dup2(pipe_fds[i][1], STDOUT_FILENO);
			close(pipe_fds[i][0]);
		}
		if (i > 0)
		{
			dup2(pipe_fds[i - 1][0], STDIN_FILENO);
			close(pipe_fds[i - 1][1]);
		}
		if (apply_redirections_to_cmd(cmd) < 0)
			exit(EXIT_FAILURE);
		if (execve(cmd->argv[0], cmd->argv, NULL) < 0)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
}

void	execute_pipes(t_command *cmd, char *const envp[])
{
	int			pipe_count;
	t_command	*head;
	int			i;
	int			pipe_fds[pipe_count - 1];

	head = cmd;
	pipe_count = count_pipes(cmd);
	while (i < pipe_count)
	{
		launch_command(cmd, i, pipe_fds);
		cmd = cmd->next;
	}
}
