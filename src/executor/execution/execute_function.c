/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaliash <vpaliash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:55:18 by vpaliash          #+#    #+#             */
/*   Updated: 2025/10/22 11:33:40 by vpaliash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	decode_errors(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
static int	check_id_after_fork(int id, char *path, t_command *cmd,
		char *const envp[])
{
	if (id < 0)
	{
		perror("fork");
		free(path);
		return (1);
	}
	if (id == 0)
	{
		execve(path, cmd->argv, envp);
		perror("execve");
		if (errno == EACCES)
			exit(126);
		else
			exit(127);
	}
	return (0);
}
int	execute(t_command *cmd, char *const envp[])
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
	if (check_id_after_fork(id, path, cmd, envp))
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
