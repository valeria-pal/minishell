/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:23:22 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/21 18:54:30 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_pipes_for_child(int i, int cmd_count, int (*pipes)[2], int pipe_count)
{
	if (pipe_count <= 0 || pipes == NULL)
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

static pid_t	launch_command(t_command *cmd, int i, int cmd_count, int (*pipes)[2], int pipe_count, t_bash *bash)
{
	pid_t	pid;
	char * path ;

	pid = fork();
	check_fork_error(pid);
	if (pid == 0)
	{
		setup_child_signals();
		path = find_path(cmd->argv[0]);
		if (!path)
	{
		print_command_not_found(cmd,bash);
		exit(127);
	}
	handle_redirections_or_exit(cmd, path);
		if (pipe_count > 0  && pipes != NULL)
			setup_pipes_for_child(i, cmd_count, pipes, pipe_count);
		if (pipe_count > 0 && pipes != NULL)
			close_pipes(pipes, pipe_count);
		execve(path, cmd->argv, bash->envp);
		perror("execve");
		free(path);
		errno_checker();
	}
	return (pid);
}

static int	wait_for_all_children(pid_t *pids, int cmd_count)
{
	int	i;
	int	status;
	int last_status;

	i = 0;
	last_status = 0;
	while (i < cmd_count)
	{
		if (waitpid(pids[i], &status, 0) == -1)
			perror("waitpid");
		else
			last_status = decode_errors(status);
		i++;
	}
	return last_status;
}

static void	run_pipeline_and_wait(t_command *cmd, int cmd_count,
				int (*pipes)[2], int pipe_count,  t_bash *bash)
{
	pid_t		*pids;
	t_command	*current;
	int			i;
	int status;

	pids = allocate_pids(cmd_count, pipes);
	current = cmd;
	i = 0;
	while (i < cmd_count && current)
	{
		pids[i] = launch_command(current, i, cmd_count,
				pipes, pipe_count, bash);
		current = current->next;
		i++;
	}
	if (pipe_count > 0 && pipes != NULL)
	{
		close_pipes(pipes, pipe_count);
		free(pipes);
	}
	status = wait_for_all_children(pids, cmd_count);
	free(pids);
	bash->last_exit_status = status;
}


void	execute_pipeline(t_command *cmd,  t_bash *bash)
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
	run_pipeline_and_wait(cmd, cmd_count, pipes, pipe_count, bash);
}