/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_and_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:21:53 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/15 12:04:31 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*strip_double_quotes_and_expand(char *str, t_bash *bash_struct)
{
	size_t	len;
	char	*inside;
	char	*expanded;

	len = ft_strlen(str);
	inside = ft_strndup(str + 1, len - 2);
	if (!inside)
		return (NULL);
	expanded = expand_variable(inside, bash_struct); // TO DO free later ????
	free(inside);
	return (expanded);
}

char	*strip_single_quotes(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	return (ft_strndup(str + 1, len - 2)); // TO DO free later ????
}

int	has_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
