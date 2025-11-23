/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:07:38 by marvin            #+#    #+#             */
/*   Updated: 2025/11/23 11:48:18 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

int	exec_builtin(t_command *cmd, t_bash *bash)
{
	int	status;
  if  (!cmd || !cmd->argv || !cmd->argv[0])
		return (-1);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		status = builtin_echo(cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		status = builtin_cd(cmd->argv, &bash->envp);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		status = builtin_pwd();
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		status = builtin_export(cmd->argv, &bash->envp);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		status = builtin_unset(cmd->argv, &bash->envp);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		status = builtin_env(bash->envp);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		status = builtin_exit(cmd->argv, bash);
	else
		return (-1);
	bash->last_exit_status = status;
	return (status);
}
