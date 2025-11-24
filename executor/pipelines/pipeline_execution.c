/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:21:54 by vpaliash          #+#    #+#             */
/*   Updated: 2025/11/23 19:45:08 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../include/minishell.h"

static void	setup_pipes_for_child(int i, int cmd_count, int (*pipes)[2],
		int pipe_count)
{
	if (pipe_count <= 0 || pipes == NULL)
		return ;
	if (i > 0)
	{
		if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2 stdin");
			exit(EXIT_FAILURE);
		}
	}
	if (i < cmd_count - 1)
	{
		if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
		{
			perror("dup2 stdout");
			exit(EXIT_FAILURE);
		}
	}
}

static void	execute_child_process(t_command *cmd, t_pipe_ctx *ctx, t_bash *bash)
{
	char	*path;

	setup_child_signals();
	path = find_path(cmd->argv[0]);
	if (!path)
	{
		print_command_not_found(cmd, bash);
		exit(127);
	}
	if (ctx->pipe_count > 0 && ctx->pipes != NULL)
		setup_pipes_for_child(ctx->i, ctx->cmd_count, ctx->pipes,
			ctx->pipe_count);
	handle_redirections_or_exit(cmd, path);
	if (ctx->pipe_count > 0 && ctx->pipes != NULL)
		close_pipes(ctx->pipes, ctx->pipe_count);
	execve(path, cmd->argv, bash->envp);
	perror("execve");
	free(path);
	errno_checker();
}

static pid_t	launch_command(t_command *cmd, t_pipe_ctx *ctx, t_bash *bash)
{
	pid_t	pid;

	pid = fork();
	check_fork_error(pid);
	if (pid == 0)
		execute_child_process(cmd, ctx, bash);
	return (pid);
}

static void	run_pipeline_and_wait(t_command *cmd, t_pipe_ctx *ctx, t_bash *bash)
{
	pid_t		*pids;
	t_command	*current;
	int			status;

	pids = allocate_pids(ctx->cmd_count, ctx->pipes);
	current = cmd;
	ctx->i = 0;
	while (ctx->i < ctx->cmd_count && current)
	{
		pids[ctx->i] = launch_command(current, ctx, bash);
		current = current->next;
		ctx->i++;
	}
	if (ctx->pipe_count > 0 && ctx->pipes != NULL)
	{
		close_pipes(ctx->pipes, ctx->pipe_count);
		free(ctx->pipes);
	}
	status = wait_for_all_children(pids, ctx->cmd_count);
	free(pids);
	bash->last_exit_status = status;
}

void	execute_pipeline(t_command *cmd, t_bash *bash)
{
	t_pipe_ctx	ctx;

	ctx.cmd_count = count_cmds(cmd);
	if (ctx.cmd_count == 0)
		return ;
	ctx.pipe_count = ctx.cmd_count - 1;
	ctx.pipes = NULL;
	ctx.i = 0;
	if (ctx.pipe_count > 0)
		ctx.pipes = create_pipes(cmd);
	run_pipeline_and_wait(cmd, &ctx, bash);
}
