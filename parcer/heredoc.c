/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 17:28:32 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/23 17:28:36 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

static int	handle_child_heredoc(char *delimiter, int fd_temp)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		write(fd_temp, line, ft_strlen(line));
		write(fd_temp, "\n", 1);
		free(line);
	}
	free(line);
	close(fd_temp);
	exit(0);
}

static int	handle_parent_heredoc(pid_t pid, int fd_temp)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	close(fd_temp);
	if (WIFSIGNALED(status))
		return (1);
	return (0);
}

int	heredoc(char *delimiter)
{
	int		fd_temp;
	pid_t	pid;

	fd_temp = open("fd_temp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_temp < 0)
		return (printf("fd_temp didn't open\n"), 1);
	pid = fork();
	if (pid == 0)
		handle_child_heredoc(delimiter, fd_temp);
	else if (pid > 0)
	{
		if (handle_parent_heredoc(pid, fd_temp))
			return (1);
	}
	else
	{
		perror("fork failed");
		return (1);
	}
	return (0);
}

int	add_heredoc_redir(t_command *cmd, t_token **tok_ptr)
{
	t_redirection	*redir_node;
	char			*filename;
	t_token			*tok;

	tok = *tok_ptr;
	if (heredoc(tok->next->value) != 0)
		return (0);
	filename = ft_strdup("fd_temp");
	if (!filename)
		return (0);
	tok = tok->next;
	redir_node = new_redirection(R_HEREDOC, filename);
	free(filename);
	if (!append_redirection(&cmd->redirs, redir_node))
		return (0);
	*tok_ptr = tok->next;
	return (1);
}