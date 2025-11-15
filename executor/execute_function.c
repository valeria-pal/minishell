/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:55:18 by vpaliash          #+#    #+#             */
/*   Updated: 2025/11/15 13:05:43 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	decode_errors(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static int	check_id_after_fork(int id, char *path, t_command *cmd,
		t_bash *bash_struct)
{
	if (id < 0)
	{
		perror("fork");
		free(path);
		return (1);
	}
	if (id == 0)
	{
		if (apply_redirections_to_cmd(cmd) < 0)
        	exit(1);
		execve(path, cmd->argv, bash_struct->envp);
		perror("execve");
		if (errno == EACCES)
			exit(126);
		else
			exit(127);
	}
	return (0);
}

int	execute(t_command *cmd, t_bash *bash_struct)
{
	pid_t	id;
	char	*path;
	int		status;

	if (!cmd || !cmd->argv)
		return (0);
	status = 0;
	path = find_path(cmd->argv[0]);
	if (!path)
		return (127);
	id = fork();
	if (check_id_after_fork(id, path, cmd, bash_struct))
		return (1);
	if (waitpid(id, &status, 0) < 0)
	{
		perror("waitpid");
		free(path);
		return (1);
	}
	free(path);
	return (decode_errors(status));
}
