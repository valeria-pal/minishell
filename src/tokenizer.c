/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:40:48 by vpozniak          #+#    #+#             */
/*   Updated: 2025/09/18 21:25:56 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

static t_toktype	get_operator_type(const char *s, int *len)
{
	if (s[0] == '|')
	{
		*len = 1;
		return (PIPE);
	}
	else if (s[0] == '<' && s[1] == '<')
	{
		*len = 2;
		return (HEREDOC);
	}
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

static int	get_word_len(const char *line, int i)
{
	int		len;
	char	q;

	len = 0;
	if (line[i] == 34 || line[i] == 39) // 34 dq 39 sq
	{
		q = line[i++];
		len++;
		while (line[i] && line[i] != q)
		{
			i++;
			len++;
		}
		if (line[i] == q) // (future) handle error if quote not closed
			len++;
		return (len);
	}
	while (line[i] && !is_space(line[i]) && line[i] != '|' && line[i] != '<'
		&& line[i] != '>')
	{
		i++;
		len++;
	}
	return (len);
}

static int	skip_spaces(const char *line, int i)
{
	while (line[i] && is_space(line[i]))
		i++;
	return (i);
}

// checks if it's an operator or a word, updates len and return type
static t_toktype	get_token_type(const char *line, int i, int *len)
{
	t_toktype	type;

	type = get_operator_type(line + i, len);
	if (type == WORD)
		*len = get_word_len(line, i);
	return (type);
}

// gets the next token, append to list
static int	process_token(const char *line, int *i, t_token **head,
		t_token **tail)
{
	int			len;
	int			start;
	char		*word;
	t_toktype	type;
	t_token		*node;

	len = 0;
	start = *i;
	type = get_token_type(line, *i, &len);
	*i += len;
	word = dup_str(line + start, len);
	if (!word)
		return (0);
	// (future) handle $VAR expansion inside double quotes here
	node = new_token(word, type);
	if (!node || !append_token(head, tail, node))
		return (0);
	return (1);
}

t_token	*tokenize(const char *line)
{
	t_token	*head;
	t_token	*tail;
	int		i;

	if (!line)
		line = "";
	head = NULL;
	tail = NULL;
	i = 0;
	while (line[i])
	{
		i = skip_spaces(line, i);
		if (!line[i])
			break ;
		if (!process_token(line, &i, &head, &tail))
			return (free_tokenlist(head), NULL);
	}
	if (!add_eol_token(&head, &tail))
		return (free_tokenlist(head), NULL);
	return (head);
}

void	tokenize_output(const char *line)
{
	t_token	*tokens;

	tokens = tokenize(line);
	if (!tokens)
	{
		printf("Tokenization failed\n");
		free((char *)line);
		return ;
	}
	print_tokens(tokens);
	// parse_tokens(tokens);
	// в будущем перед очищением стракта парсинг и екзекьютинг сделать
	// execute_commands();
	free_tokenlist(tokens);
}
