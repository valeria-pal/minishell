/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 21:46:49 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/18 15:04:11 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	child_heredoc(char *delimiter, int fd)
// {
// 	char	*line;

// 	signal(SIGINT, SIG_DFL);
// 	while (1)
// 	{
// 		line = readline("heredoc> ");
// 		if (!line || ft_strcmp(line, delimiter) == 0)
// 			break ;
// 		write(fd, line, ft_strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
// 	}
// 	free(line);
// 	close(fd);
// 	exit(0);
// }

// int	parent_heredoc(pid_t pid, int fd)
// {
// 	int	status;

// 	signal(SIGINT, SIG_IGN);
// 	waitpid(pid, &status, 0);
// 	close(fd);
// 	if (WIFSIGNALED(status))
// 		return (1);
// 	return (0);
// }

// int	heredoc_create(char *delimiter, char *outfile)
// {
// 	int		fd;
// 	pid_t	pid;

// 	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd < 0)
// 		return (perror(outfile), 1);
// 	pid = fork();
// 	if (pid < 0)
// 		return (perror("fork"), close(fd), 1);
// 	if (pid == 0)
// 		child_heredoc(delimiter, fd);
// 	if (parent_heredoc(pid, fd))
// 		return (1);
// 	return (0);
// }

// int	add_heredoc_redir(t_command *cmd, t_token **tok_ptr)
// {
// 	t_redirection *node;
// 	char *file;

// 	file = ft_strdup("fd_temp");
// 	if (heredoc_create((*tok_ptr)->next->value, file))
// 		return (free(file), 0);
// 	node = new_redirection(R_HEREDOC, file);
// 	if (!node || !append_redirection(&cmd->redirs, node))
// 		return (0);
// 	*tok_ptr = (*tok_ptr)->next;
// 	return (1);
// }

int	add_heredoc_redir(t_command *cmd, t_token **tok_ptr)
{
	t_redirection	*node;
	char			temp_name[64];
	t_token			*tok;
	static int		counter = 0;

	tok = *tok_ptr;
	if (!tok->next || tok->next->type != WORD)
		return (0);
	// Use stack-allocated filename to avoid memory issues
	snprintf(temp_name, sizeof(temp_name), ".heredoc_temp_%d_%d", getpid(),
		counter++);
	if (heredoc_create(tok->next->value, temp_name))
		return (0);
	// Use strdup only once for the node
	node = new_redirection(R_HEREDOC, ft_strdup(temp_name));
	if (!node)
		return (0);
	if (!append_redirection(&cmd->redirs, node))
	{
		free(node->filename);
		free(node);
		return (0);
	}
	*tok_ptr = tok->next->next;
	return (1);
}

void	child_heredoc(char *delimiter, int fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file\n",
				2);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	exit(0);
}

int	parent_heredoc(pid_t pid, int fd)
{
	int	status;

	close(fd); // Close parent's copy of the file descriptor
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		// If child was interrupted by signal (e.g., Ctrl+C)
		return (1);
	}
	return (0);
}

int	heredoc_create(char *delimiter, char *outfile)
{
	int fd;
	pid_t pid;

	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(outfile), 1);

	pid = fork();
	if (pid < 0)
	{
		close(fd);
		unlink(outfile); // Clean up temporary file
		return (perror("fork"), 1);
	}

	if (pid == 0)
		child_heredoc(delimiter, fd);
	else
	{
		if (parent_heredoc(pid, fd))
		{
			unlink(outfile); // Clean up on error
			return (1);
		}
	}

	return (0);
}