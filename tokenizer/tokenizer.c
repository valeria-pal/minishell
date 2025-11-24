/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:40:48 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/24 17:04:55 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

static int	get_word_len(const char *line, int i)
{
	int		len;
	char	q;

	len = 0;
	if (line[i] == SQ || line[i] == DQ)
	{
		q = line[i++];
		len++;
		while (line[i] && line[i] != q)
		{
			i++;
			len++;
		}
		if (line[i] == q)
			len++;
		return (len);
	}
	while (line[i] && !is_space(line[i]) && line[i] != '|' && line[i] != '<'
		&& line[i] != '>' && (line[i] != DQ && line[i] != SQ))
	{
		i++;
		len++;
	}
	return (len);
}

static t_toktype	get_token_type(const char *line, int i, int *len)
{
	t_toktype	type;

	type = get_operator_type(line + i, len);
	if (type == WORD)
		*len = get_word_len(line, i);
	return (type);
}

int	process_token(const char *line, int *i, t_token **head, t_token **tail)
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
	word = ft_strndup(line + start, len);
	if (!word)
		return (0);
	node = new_token(word, type);
	if (!node || !append_token(head, tail, node))
		return (free(word), 0);
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

void	tokenize_output(const char *line, t_bash *bash_struct)
{
	t_token		*tokens;
	t_command	*commands;

	tokens = tokenize(line);
	if (!tokens)
	{
		printf("Tokenization failed\n");
		return ;
	}
	if (check_syntax_errors(tokens))
	{
		free_tokenlist(tokens);
		return ;
	}
	commands = parse_pipeline(tokens, bash_struct);
	if (!commands)
	{
		free_tokenlist(tokens);
		return ;
	}
	execute(commands, bash_struct);
	free_tokenlist(tokens);
	free_commands(commands);
}
