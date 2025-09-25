/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 20:56:42 by vpozniak          #+#    #+#             */
/*   Updated: 2025/09/25 20:53:16 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

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

/*
When you free(tok), you lose access to tok->next.

So you store tok->next in next before freeing the current node.

Then move on to tok = next.*/
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
	t_token	*eol;

	eol = new_token(NULL, EOL);
	if (!eol)
		return (0);
	return (append_token(head, tail, eol));
}

int	skip_spaces(const char *line, int i)
{
	while (line[i] && is_space(line[i]))
		i++;
	return (i);
}
