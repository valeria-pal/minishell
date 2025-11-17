/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 21:46:49 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/17 22:44:32 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_heredoc(char *delimiter, int fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	exit(0);
}

int	parent_heredoc(pid_t pid, int fd)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	close(fd);
	if (WIFSIGNALED(status))
		return (1);
	return (0);
}

int	heredoc_create(char *delimiter, char *outfile)
{
	int		fd;
	pid_t	pid;

	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(outfile), 1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), close(fd), 1);
	if (pid == 0)
		child_heredoc(delimiter, fd);
	if (parent_heredoc(pid, fd))
		return (1);
	return (0);
}

int	add_heredoc_redir(t_command *cmd, t_token **tok_ptr)
{
	t_redirection *node;
	char *file;

	file = ft_strdup("fd_temp");
	if (heredoc_create((*tok_ptr)->next->value, file))
		return (free(file), 0);
	node = new_redirection(R_HEREDOC, file);
	if (!node || !append_redirection(&cmd->redirs, node))
		return (0);
	*tok_ptr = (*tok_ptr)->next;
	return (1);
}