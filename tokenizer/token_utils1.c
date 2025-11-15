/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:51:12 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/15 12:05:04 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_toktype	heredoc(int *len)
{
	*len = 2;
	return (HEREDOC);
}

t_toktype	get_operator_type(const char *s, int *len)
{
	if (s[0] == '|')
	{
		*len = 1;
		return (PIPE);
	}
	else if (s[0] == '<' && s[1] == '<')
		heredoc(len);
	else if (s[0] == '<')
	{
		*len = 1;
		return (REDIR_IN);
	}
	else if (s[0] == '>' && s[1] == '>')
	{
		*len = 2;
		return (REDIR_APPEND);
	}
	else if (s[0] == '>')
	{
		*len = 1;
		return (REDIR_OUT);
	}
	return (WORD);
}
