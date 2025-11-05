/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:52:49 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/04 16:15:17 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

char	*my_getenv(char **env, const char *name)
{
	int		i;
	size_t	len;

	i = 0;
	len = strlen(name);
	while (env[i])
	{
		if (strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1); // return pointer to value
		i++;
	}
	return (NULL);
}

// char	**copy_env(char **envp)
// {
// 	int		i;
// 	char	**copy;

// 	i = 0;
// 	while (envp[i])
// 		i++;
// 	copy = malloc(sizeof(char *) * (i + 1));
// 	if (!copy)
// 		return (NULL);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		copy[i] = strdup(envp[i]);
// 		if (!copy[i])
// 		{
// 			while (--i >= 0)
// 				free(copy[i]);
// 			free(copy);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	copy[i] = NULL;
// 	return (copy);
// }

static char	*append_char(char *result, char c)
{
	char	tmp[2];
	char	*new;

	tmp[0] = c;
	tmp[1] = '\0';
	new = ft_strjoin(result, tmp);
	free(result);
	return (new);
}

static char	*append_var_value(char *str, int *i, char *result, char **envp)
{
	int		start;
	char	*var_name;
	char	*value;
	char	*tmp;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_strndup(str + start, *i - start);
	value = my_getenv(envp, var_name);
	free(var_name);
	if (!value)
		value = "";
	tmp = ft_strjoin(result, value);
	free(result);
	return (tmp);
}

char	*expand_variable(char *str, char **envp)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
				result = append_var_value(str, &i, result, envp);
			else
				result = append_char(result, '$');
		}
		else
			result = append_char(result, str[i++]);
	}
	return (result);
}
