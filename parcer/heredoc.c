/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 21:46:49 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/19 14:57:56 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*create_heredoc_filename(void)
{
	static unsigned int	counter;
	char				buf[128];

	if (snprintf(buf, sizeof(buf), "/tmp/minishell_hd_%d_%u.tmp",
			(int)getpid(), counter++) < 0)
		return (NULL);
	return (ft_strdup(buf));
}

void	child_heredoc(char *delimiter, int fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
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
	struct sigaction	old_int;
	struct sigaction	old_quit;
	struct sigaction	ignore;
	int					status;

	ft_memset(&ignore, 0, sizeof(ignore));
	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	sigaction(SIGINT, &ignore, &old_int);
	sigaction(SIGQUIT, &ignore, &old_quit);
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		sigaction(SIGINT, &old_int, NULL);
		sigaction(SIGQUIT, &old_quit, NULL);
		close(fd);
		return (1);
	}
	sigaction(SIGINT, &old_int, NULL);
	sigaction(SIGQUIT, &old_quit, NULL);
	close(fd);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	return (0);
}

int	heredoc_create(char *delimiter, char *outfile)
{
	int		fd;
	pid_t	pid;

	if (!delimiter || !outfile)
		return (1);
	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (perror(outfile), 1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), close(fd), 1);
	if (pid == 0)
		child_heredoc(delimiter, fd);
	if (parent_heredoc(pid, fd))
	{
		unlink(outfile);
		return (1);
	}
	return (0);
}

int	add_heredoc_redir(t_command *cmd, t_token **tok_ptr)
{
	t_redirection	*node;
	char			*file;
	t_token			*tok;

	if (!cmd || !tok_ptr || !*tok_ptr || !(*tok_ptr)->next)
		return (0);
	tok = *tok_ptr;
	file = create_heredoc_filename();
	if (!file)
		return (0);
	if (heredoc_create(tok->next->value, file))
		return (unlink(file), free(file), 0);
	node = new_redirection(R_HEREDOC, file);
	if (!node)
		return (unlink(file), free(file), 0);
	free(file);
	if (!append_redirection(&cmd->redirs, node))
	{
		unlink(node->filename);
		free(node->filename);
		free(node);
		return (0);
	}
	*tok_ptr = tok->next->next;
	return (1);
}
