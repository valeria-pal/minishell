/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:21:54 by vpaliash          #+#    #+#             */
/*   Updated: 2025/11/20 19:14:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static 	setup_pipes_for_child(int i, int cmd_count, int (*pipes)[2], int pipe_count)
{
	if (pipe_count <= 0)
		return;
	
	if (i > 0) // if not first read from previous pipe
	{
		if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2 stdin");
			exit(EXIT_FAILURE);
		}
	}
	if (i < cmd_count - 1) //if not last write into current pipe
	{
		if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
		{
			perror("dup2 stdout");
			exit(EXIT_FAILURE);
		}
	}
}

static pid_t	launch_command(t_command *cmd, int i, int cmd_count,
			int (*pipes)[2], int pipe_count, char **envp)
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
		if (pipe_count > 0)
			setup_pipes_for_child(i, cmd_count, pipes, pipe_count);
		close_pipes(pipes, pipe_count);
		if (apply_redirections_to_cmd(cmd) < 0)
			exit(EXIT_FAILURE);
		execve(cmd->argv[0], cmd->argv, envp);
		perror("execve");
		exit(127);
	}
	return (pid);
}

static void	wait_for_all_children(pid_t *pids, int cmd_count)
{
	int	i;
	int	status;

	i = 0;
	while (i < cmd_count)
	{
		if (waitpid(pids[i], &status, 0) == -1)
			perror("waitpid");
		i++;
	}
}

static static void	run_pipeline_and_wait(t_command *cmd, int cmd_count,
				int (*pipes)[2], int pipe_count, char **envp)
{
	pid_t		*pids;
	t_command	*current;
	int			i;

	pids = allocate_pids(cmd_count, pipes);
	current = cmd;
	i = 0;
	while (i < cmd_count && current)
	{
		pids[i] = launch_command(current, i, cmd_count,
				pipes, pipe_count, envp);
		current = current->next;
		i++;
	}
	if (pipe_count > 0)
	{
		close_pipes(pipes, pipe_count);
		free(pipes);
	}
	i = 0;
	wait_for_all_children(pids, cmd_count);

	free(pids);
}

void	execute_pipeline(t_command *cmd, char **envp)
{
	int		(*pipes)[2];
	int		cmd_count;
	int		pipe_count;

	cmd_count = count_cmds(cmd);
	if (cmd_count == 0)
		return;
	pipe_count = cmd_count - 1;
	pipes = NULL;
	if (pipe_count > 0)
		pipes = create_pipes(cmd);
	run_pipeline_and_wait(cmd, cmd_count, pipes, pipe_count, envp);
}


	

