/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:40:48 by vpozniak          #+#    #+#             */
/*   Updated: 2025/09/09 12:19:57 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	add_word_token(const char *start, size_t len, t_token **head,
		t_token **tail)
{
	char	*w;
	t_token	*node;

	w = dup_str(start, len);
	if (!w)
		return (0);
	node = new_token(w, WORD);
	if (!node)
	{
		free(w);
		return (0);
	}
	return (append_token(head, tail, node));
}

int	add_eol_token(t_token **head, t_token **tail)
{
	t_token	*eol;

	eol = new_token(NULL, EOL);
	if (!eol)
		return (0);
	return (append_token(head, tail, eol));
}

t_token	*tokenize(const char *line)
{
	size_t	i;
	size_t	start;
	t_token	*head;
	t_token	*tail;

	head = NULL;
	tail = NULL;
	i = 0;
	if (!line)
		line = "";
	while (line[i])
	{
		while (line[i] && is_space(line[i]))
			i++;
		if (!line[i])
			break ;
		start = i;
		while (line[i] && !is_space(line[i]))
			i++;
		if (!add_word_token(line + start, i - start, &head, &tail))
			return (free_tokenlist(head), NULL);
	}
	if (!add_eol_token(&head, &tail))
		return (free_tokenlist(head), NULL);
	return (head);
}
