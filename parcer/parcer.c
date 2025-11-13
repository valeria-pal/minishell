/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:41:58 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/13 12:14:11 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

static char	*normalize_word(char *original_word, t_bash *bash_struct)
{
	if (original_word[0] == SQ)
		return (strip_single_quotes(original_word));
	if (original_word[0] == DQ)
		return (strip_double_quotes_and_expand(original_word, bash_struct));
	if (has_dollar(original_word))
		return (expand_variable(ft_strdup(original_word), bash_struct));
	return (ft_strdup(original_word));
}

static int	count_args_until_pipe(t_token *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type != PIPE && tok->type != EOL)
	{
		if (tok->type == WORD)
			count++;
		else if (tok->type == REDIR_IN || tok->type == REDIR_OUT
			|| tok->type == REDIR_APPEND || tok->type == HEREDOC)
			// TODO check if works with only else
			tok = tok->next;
		tok = tok->next;
	}
	return (count);
}

static int	add_redirection(t_command *cmd, t_token **tok_ptr)
{
	t_redir_type	rtype;
	t_redirection	*redir_node;
	t_token			*tok;

	tok = *tok_ptr;
	if (tok->type == REDIR_IN)
		rtype = R_IN;
	else if (tok->type == REDIR_OUT)
		rtype = R_OUT;
	else if (tok->type == REDIR_APPEND)
		rtype = R_APPEND;
	else
		rtype = R_HEREDOC;
	tok = tok->next;
	redir_node = new_redirection(rtype, tok->value);
	if (!append_redirection(&cmd->redirs, redir_node))
		return (0);
	*tok_ptr = tok->next;
	return (1);
}

static t_command	*parse_one_command(t_token **tok_ptr, t_bash *bash_struct)
{
	t_command	*cmd;
	t_token		*tok;
	int			i;

	cmd = cmd_new();
	if (!cmd)
		return (NULL);
	if (count_args_until_pipe(*tok_ptr) > 0)
	{
		cmd->argv = malloc(sizeof(char *) * (count_args_until_pipe(*tok_ptr)
					+ 1));
		if (!cmd->argv)
			return (free(cmd), NULL);
	}
	i = 0;
	tok = *tok_ptr;
	while (tok && tok->type != PIPE && tok->type != EOL)
	{
		if (tok->type == WORD)
		{
			cmd->argv[i] = normalize_word(tok->value, bash_struct);
			if (!cmd->argv[i])
				return (free_commands(cmd), NULL);
			i++;
			tok = tok->next;
		}
		else if (!add_redirection(cmd, &tok))
			return (free_commands(cmd), NULL);
	}
	if (count_args_until_pipe(*tok_ptr) > 0)
		cmd->argv[i] = NULL;
	*tok_ptr = tok;
	return (cmd);
}

t_command	*parse_pipeline(t_token *tokens, t_bash *bash_struct)
{
	t_command	*head;
	t_command	*tail;
	t_command	*cmd;

	head = NULL;
	tail = NULL;
	while (tokens && tokens->type != EOL)
	{
		cmd = parse_one_command(&tokens, bash_struct);
		if (!cmd)
			return (free_commands(head), NULL);
		if (!head)
			head = cmd;
		else
			tail->next = cmd;
		tail = cmd;
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (head);
}
