/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:10:06 by vpaliash          #+#    #+#             */
/*   Updated: 2025/09/18 21:03:57 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tokens(t_token *t)
{
	while (t)
	{
		if (t->type == WORD && t->value)
			printf("WORD: %s\n", t->value);
		else if (t->type == PIPE)
			printf("PIPE: |\n");
		else if (t->type == REDIR_IN)
			printf("REDIR_IN: <\n");
		else if (t->type == REDIR_OUT)
			printf("REDIR_OUT: >\n");
		else if (t->type == REDIR_APPEND)
			printf("REDIR_APPEND: >>\n");
		else if (t->type == HEREDOC)
			printf("HEREDOC: <<\n");
		else if (t->type == EOL)
			printf("EOL\n");
		t = t->next;
	}
}

int	append_token(t_token **head, t_token **tail, t_token *node)
{
	if (!node)
		return (0);
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
	return (1);
}

void	free_tokenlist(t_token *tok)
{
	t_token	*next;

	while (tok)
	{
		next = tok->next;
		if (tok->value)
			free(tok->value);
		free(tok);
		tok = next;
	}
}

t_token	*new_token(char *value, t_toktype type)
{
	t_token	*t;

	t = (t_token *)malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	t->value = value;
	t->type = type;
	t->next = NULL;
	return (t);
}

int	add_eol_token(t_token **head, t_token **tail)
{
	t_token *eol;

	eol = new_token(NULL, EOL);
	if (!eol)
		return (0);
	return (append_token(head, tail, eol));
}