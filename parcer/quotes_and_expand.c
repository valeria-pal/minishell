/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_and_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:21:53 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/04 16:23:51 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

char	*strip_double_quotes_and_expand(char *str, char **envp)
{
	size_t	len;
	char	*inside;
	char	*expanded;

	len = ft_strlen(str);
	// if (str[0] == '"') // len >= 2 && str[len - 1] == '"'
	// {
	inside = ft_strndup(str + 1, len - 2);
	if (!inside)
		return (NULL);
	expanded = expand_variable(inside, envp);
	// if there is nothing to expand it returns the the duplicated string that you need to free later
	free(inside);
	return (expanded);
	// }
	// return (expand_variable(ft_strdup(str)));
}
/*
return (expand_variable(ft_strdup(str)));
^
|
|
if inside	normalize_word(void) you call expand_variable(original) directly,
and	expand_variable(void) modifies or frees it,
		you’re corrupting the tokenizer’s memory.
That pointer (tok->value) might still be used elsewhere or freed later → use-after-free or double free.
*/

char	*strip_single_quotes(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	// if (str[0] == '\'') //&& str[len - 1] == '\'' && len >= 2
	return (ft_strndup(str + 1, len - 2)); // TO DO free later ????
											// return (ft_strdup(str));
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
