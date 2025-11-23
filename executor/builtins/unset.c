/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:51:36 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/23 21:00:00 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../include/minishell.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	find_env_index(char **envp, const char *key)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0
			&& (envp[i][len] == '=' || envp[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static void	remove_env_var(char ***envp, int index)
{
	int		i;
	int		count;
	char	**new_env;

	count = 0;
	while ((*envp)[count])
		count++;
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return ;
	i = 0;
	while (i < index)
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	free((*envp)[index]);
	while (i < count - 1)
	{
		new_env[i] = (*envp)[i + 1];
		i++;
	}
	new_env[i] = NULL;
	free(*envp);
	*envp = new_env;
}

static int	validate_and_unset(char *arg, char ***envp)
{
	int	index;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	index = find_env_index(*envp, arg);
	if (index != -1)
		remove_env_var(envp, index);
	return (0);
}

int	builtin_unset(char **argv, char ***envp)
{
	int	i;
	int	status;

	status = 0;
	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		if (validate_and_unset(argv[i], envp))
			status = 1;
		i++;
	}
	return (status);
}
