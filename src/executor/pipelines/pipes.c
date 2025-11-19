/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaliash <vpaliash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:21:54 by vpaliash          #+#    #+#             */
/*   Updated: 2025/11/19 20:39:41 by vpaliash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	count_cmds(t_command *cmd)
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
void	close_pipes(int pipe_fds[][2], int last_index)
{
	last_index--;
	while (last_index >= 0)
	{
		close(pipe_fds[last_index][0]);
		close(pipe_fds[last_index][1]);
		last_index--;
	}
}
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

int (*create_pipes(t_command *cmd))[2]
{
	int(*pipes)[2];
	int pipe_count;
	int i;

	i = 0;
	pipe_count = count_cmds(cmd) - 1 ;
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
		pipe_error_check(pipes, i); // creates pipe and checks for error
		i++;
	}
	return (pipes);
}


void execute_pipeline(t_command * cmd, char **envp)
{
	
}

void	launch_command(t_command *cmd, int i, int pipe_fds[][2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) // child process
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
