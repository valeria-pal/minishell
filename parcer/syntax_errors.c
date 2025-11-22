/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:08:13 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/15 12:04:35 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	error_message(char *err)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("`\n", 2);
	return (1);
}

static int	check_pipe_errors(t_token *tok)
{
	t_token	*prev;

	prev = NULL;
	while (tok && tok->type != EOL)
	{
		if (tok->type == PIPE)
		{
			if (!prev || prev->type == PIPE)
				return (error_message("|"));
			if (!tok->next || tok->next->type == EOL)
				return (error_message("newline"));
		}
		prev = tok;
		tok = tok->next;
	}
	return (0);
}

static int	check_redirection_errors(t_token *tok)
{
	while (tok)
	{
		if ((tok->type == REDIR_IN || tok->type == REDIR_OUT
				|| tok->type == REDIR_APPEND || tok->type == HEREDOC))
		{
			if (!tok->next || tok->next->type != WORD)
			// или если предыдузуее не слово
			{
				if (tok->next && tok->next->value)
					return (error_message("redirection"));
				else
					return (error_message("newline"));
			}
		}
		tok = tok->next;
	}
	return (0);
}

static int	check_unclosed_quotes(t_token *tok)
{
	int		i;
	char	open;

	while (tok)
	{
		if (tok->type == WORD && tok->value)
		{
			i = 0;
			open = 0;
			while (tok->value[i])
			{
				if (!open && (tok->value[i] == SQ || tok->value[i] == DQ))
					open = tok->value[i];
				else if (open && tok->value[i] == open)
					open = 0;
				i++;
			}
			if (open)
				return (ft_putstr_fd("syntax error: unclosed quote\n", 2), 1);
		}
		tok = tok->next;
	}
	return (0);
}

int	check_syntax_errors(t_token *tokens)
{
	if (check_pipe_errors(tokens))
		return (1);
	if (check_redirection_errors(tokens))
		return (1);
	if (check_unclosed_quotes(tokens))
		return (1);
	// potential check for nonsense word tokens
	return (0);
}
