/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:38:31 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/15 12:04:20 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_redirection	*new_redirection(t_redir_type type, char *filename)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->filename = ft_strdup(filename);
	redir->next = NULL;
	return (redir);
}

// Helper: append redirection to list
int	append_redirection(t_redirection **head, t_redirection *node)
{
	t_redirection	*tmp;

	if (!node)
		return (0);
	if (!*head)
		*head = node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	return (1);
}

// Helper: free redirections
void	free_redirections(t_redirection *head)
{
	t_redirection	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->filename);
		free(head);
		head = tmp;
	}
}

// Helper: free commands
void	free_commands(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
			{
				free(cmd->argv[i]);
				i++;
			}
			free(cmd->argv);
		}
		free_redirections(cmd->redirs);
		free(cmd);
		cmd = tmp;
	}
}

t_command	*cmd_new(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}
