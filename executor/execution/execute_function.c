/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:55:18 by vpaliash          #+#    #+#             */
/*   Updated: 2025/11/21 18:52:46 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static int	decode_errors(int status)
// {
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	if (WIFSIGNALED(status))
// 		return (128 + WTERMSIG(status));
// 	return (1);
// }

// static int	check_id_after_fork(int id, char *path, t_command *cmd,
// 		t_bash *bash_struct)
// {
// 	if (id < 0)
// 	{
// 		perror("fork");
// 		free(path);
// 		return (1);
// 	}
// 	if (id == 0)
// 	{
// 		if (apply_redirections_to_cmd(cmd) < 0)
//         	exit(1);
// 		execve(path, cmd->argv, bash_struct->envp);
// 		perror("execve");
// 		if (errno == EACCES)
// 			exit(126);
// 		else
// 			exit(127);
// 	}
// 	return (0);
// }

// int	execute(t_command *cmd, t_bash *bash_struct)
// {
// 	pid_t	id;
// 	char	*path;
// 	int		status;

// 	if (!cmd || !cmd->argv)
// 		return (0);
// 	status = 0;
// 	path = find_path(cmd->argv[0]);
// 	if (!path)
// 		return (127);
// 	id = fork();
// 	if (check_id_after_fork(id, path, cmd, bash_struct))
// 		return (1);
// 	if (waitpid(id, &status, 0) < 0)
// 	{
// 		perror("waitpid");
// 		free(path);
// 		return (1);
// 	}
// 	free(path);
// 	return (decode_errors(status));
// }
 int	decode_errors(int status)
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
		if (apply_redirections_to_cmd(cmd) < 0)
			exit(1);
		execve(path, cmd->argv, envp);
		perror("execve");
		free(path);
		if (errno == EACCES)
		exit(126);
		else if (errno == ENOENT)
			exit(127);
		else
			exit(1);
	}
	return (0);
}
void print_command_not_found(t_command *cmd, t_bash *bash)
{
	write(2, "minishell: ", 11);
		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(2, ": command not found\n", 20);
		bash->last_exit_status = 127;
		return;
}
void	execute_one_cmd(t_command *cmd, t_bash *bash )
{
	pid_t	id;
	char	*path;
	int		status;

	path = find_path(cmd->argv[0]);
	if (!path)
	{
		print_command_not_found(cmd,bash);
		return;
	}
	id = fork();
	if (check_id_after_fork(id, path, cmd, bash->envp))
		{
		bash->last_exit_status = 1;
		return;
	}
	if (waitpid(id, &status, 0) < 0)
	{
		perror("waitpid");
		bash->last_exit_status = 1;
		return;
	}
	free(path);
	bash->last_exit_status = decode_errors(status);
}
void execute(t_command *cmd, t_bash *bash)
{
    int cmd_count;

	cmd_count = count_cmds(cmd);

	if (!cmd )
		return;
	//if (cmd_count == 1 && cmd->argv && cmd->argv[0] && exec_builtin(cmd, bash) != -1)
	//	return;
	if (cmd_count == 1)
		execute_one_cmd(cmd, bash);
	else
		execute_pipeline(cmd, bash);
}