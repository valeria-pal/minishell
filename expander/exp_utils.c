/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:52:49 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/14 20:43:23 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

char	*my_getenv(t_bash *bash_struct, const char *name)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (bash_struct->envp[i])
	{
		if (ft_strncmp(bash_struct->envp[i], name, len) == 0
			&& bash_struct->envp[i][len] == '=')
			return (bash_struct->envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

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

static char	*append_var_value(char *str, int *i, char *result,
		t_bash *bash_struct)
{
	int		start;
	char	*var_name;
	char	*value;
	char	*tmp;

	start = *i;
	while (str[*i] && str[*i] != 32)
		(*i)++;
	var_name = ft_strndup(str + start, *i - start);
	value = my_getenv(bash_struct, var_name);
	free(var_name);
	if (!value)
		return (result);
	tmp = ft_strjoin(result, value);
	free(result);
	return (tmp);
}

static char	*qmark_gv(char *result, t_bash *bash_struct, int *i)
{
	char	*temp;
	char	*exit_status;

	exit_status = ft_itoa(bash_struct->last_exit_status);
	temp = ft_strjoin(result, exit_status); // free temp??
	free(exit_status);
	free(result);
	result = temp;
	(*i)++;
	return (result);
}

char	*expand_variable(char *str, t_bash *bash_struct)
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
			if (str[i] == '?')
				result = qmark_gv(result, bash_struct, &i);
			else if (str[i])
				result = append_var_value(str, &i, result, bash_struct);
			else
				result = append_char(result, '$');
		}
		else
			result = append_char(result, str[i++]);
	}
	return (result); // have to free later
}
