/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaliash <vpaliash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:10:06 by vpaliash          #+#    #+#             */
/*   Updated: 2025/10/22 11:28:32 by vpaliash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	print_tokens(t_token *t)
{
	while (t)
	{
		if (t->type == WORD)
			printf("WORD: %s\n", t->value);
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
	t_token *next;

	while (tok)
	{
		next = tok->next;
		if (tok->value)
			free(tok->value);
		free(tok);
		tok = next;
	}
}