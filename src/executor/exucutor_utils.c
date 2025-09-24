/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exucutor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaliash <vpaliash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:55:18 by vpaliash          #+#    #+#             */
/*   Updated: 2025/09/24 14:30:21 by vpaliash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	execute(t_cmd *cmd, char *const envp[])
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);

	pid_t id;
	char *path;
	int status = 0;

	path = cmd->args[0];

	id = fork();
	if (id < 0)
	{
		perror("fork");
		return (1);
	}
	if (id == 0)
	{
		execve(path, cmd->args, envp) ;
		perror("execve");
	if (errno == EACCES)
			_exit(126);
		else
			_exit(127);
	}

	if (waitpid(id, &status, 0) < 0)
	{
		perror("waitpid");
		return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));

	return (1);
}
