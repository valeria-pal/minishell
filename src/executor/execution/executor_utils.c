/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaliash <vpaliash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:15:09 by vpaliash          #+#    #+#             */
/*   Updated: 2025/10/22 14:52:33 by vpaliash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	*release_command_with_backslash_and_path(char *result,
		char *cmd_with_backslash, char **start)
{
	free(cmd_with_backslash);
	free_split(start);
	return (result);
}

static char	*build_candidate_path(const char *cmd, const char *envp_path)
{
	char	*candidate_path;
	char	**all_pathes_from_envp;
	char	*cmd_with_backslash;
	char	**start;

	cmd_with_backslash = ft_strjoin("/", cmd);
	all_pathes_from_envp = ft_split(envp_path, ':');
	start = all_pathes_from_envp;
	if (!cmd_with_backslash || !all_pathes_from_envp)
		return (release_command_with_backslash_and_path(NULL, cmd_with_backslash,
				start));
	while (*all_pathes_from_envp)
	{
		candidate_path = ft_strjoin(*all_pathes_from_envp, cmd_with_backslash);
		if (!candidate_path)
			return (release_command_with_backslash_and_path(NULL,
					cmd_with_backslash, start));
		if (!access(candidate_path, X_OK))
			return (release_command_with_backslash_and_path(candidate_path,
					cmd_with_backslash, start));
		all_pathes_from_envp++;
		free(candidate_path);
	}
	return (release_command_with_backslash_and_path(NULL, cmd_with_backslash,
			start));
}

char	*find_path(const char *cmd)
{
	char	*envp_path;
	char	*candidate_path;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	envp_path = ft_strdup(getenv("PATH"));
	// it is important to make a copy because then it can be modified with built in commands
	if (!envp_path)
		return (NULL);
	candidate_path = build_candidate_path(cmd, envp_path);
	free(envp_path);
	return (candidate_path);
}


