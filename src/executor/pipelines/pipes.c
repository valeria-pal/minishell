/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:21:54 by vpaliash          #+#    #+#             */
/*   Updated: 2025/11/20 16:47:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	count_cmds(t_command *cmd)
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
	int i ;
	i = 0;
	while (i < pipe_count)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
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
		pipe_error_check(pipes, i); // close  pipe and checks for error
		i++;
	}
	return (pipes);
}


pid_t launch_command (t_command *cmd,int i, int cmd_count, int (*pipes)[2],int pipe_count, char **envp)
{
	pid_t pid ;

	pid= fork();
	
	if (pid< 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (pipe_count > 0)
		{
			if (i> 0)
			{
				if (dup2(pipes[i-1][0], STDIN_FILENO) == -1)
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
		close_pipes(pipes, pipe_count);
		if (apply_all_redirections (cmd) < 0)
		exit(EXIT_FAILURE);
		
		execve(cmd->argv[0], cmd-> argv, envp);
		perror("execve");
		exit(127);
	}
		return pid;
	
	}



void execute_pipeline(t_command * cmd, char **envp)
{
	pid_t *pids;
	int(*pipes)[2];
	int cmd_count;
	t_command *current;
	int status;
	int i;
	
	current = cmd;
	i = 0;
	cmd_count = count_cmds(cmd);
	pipes = NULL;

	if (cmd_count == 0)
	return;
	if (cmd_count -1 > 0)
	pipes = create_pipes(cmd);
	
	pids = malloc(cmd_count * sizeof(pid_t));
	if(!pids)
	{
	perror("malloc");
	if(pipes)
	free(pipes);
	exit(EXIT_FAILURE);
	}
	while (i < cmd_count && current)
	{
		pids[i] = launch_command(current,i,cmd_count, pipes, cmd_count - 1, envp);
		current = current-> next;
		i++;
	}
	   if (cmd_count-1 > 0)
    {
        close_pipes(pipes, cmd_count -1);
        free(pipes);
    }
	i = 0;
	while (i < cmd_count  )
		{
			if( waitpid(pids[i], &status, 0 ) == -1)
			perror("waitpid");
			i++;
		}
		free(pids);
	}
	

	

