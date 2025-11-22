/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:28:19 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/15 12:04:57 by vpozniak         ###   ########.fr       */
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
