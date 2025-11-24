/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:42:00 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/24 16:47:34 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../include/minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	find_env_var(char **envp, const char *key, size_t key_len)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0
			&& (envp[i][key_len] == '=' || envp[i][key_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

char	**realloc_env(char **old_env, int new_size)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (new_size + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (old_env[i])
	{
		new_env[i] = old_env[i];
		i++;
	}
	new_env[i] = NULL;
	free(old_env);
	return (new_env);
}

int	update_env_var(char ***envp, char *arg)
{
	char	*equals;
	int		index;
	char	*new_var;

	equals = ft_strchr(arg, '=');
	if (!equals)
		return (0);
	index = find_env_var(*envp, arg, equals - arg);
	new_var = ft_strdup(arg);
	if (!new_var)
		return (-1);
	if (index != -1)
	{
		free((*envp)[index]);
		(*envp)[index] = new_var;
	}
	else
	{
		*envp = realloc_env(*envp, count_env(*envp) + 1);
		if (!*envp)
			return (free(new_var), -1);
		(*envp)[count_env(*envp)] = new_var;
		(*envp)[count_env(*envp) + 1] = NULL;
	}
	return (0);
}

void	print_all_exports(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(envp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

