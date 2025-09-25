/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaliash <vpaliash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:55:18 by vpaliash          #+#    #+#             */
/*   Updated: 2025/09/25 17:42:14 by vpaliash         ###   ########.fr       */
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
static int	check_id_after_fork(int id, char *path, t_cmd *cmd,
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
		execve(path, cmd->args, envp);
		perror("execve");
		if (errno == EACCES)
			exit(126);
		else
			exit(127);
	}
	return (0);
}
int	execute(t_cmd *cmd, char *const envp[])
{
	pid_t	id;
	char	*path;
	int		status;

	if (!cmd || !cmd->args)
		return (0);
	status = 0;
	path = find_path(cmd->args[0]);
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
