/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:28:07 by vpaliash          #+#    #+#             */
/*   Updated: 2025/11/18 17:56:22 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	apply_rd_in(t_redirection *rd)
{
	int	fd;

	fd = open(rd->filename, O_RDONLY);
	if (fd < 0)
	{
		perror(rd->filename);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 stdin");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	apply_rd_out(t_redirection *rd)
{
	int	fd;

	fd = open(rd->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(rd->filename);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 stdout");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	apply_rd_append(t_redirection *rd)
{
	int	fd;

	fd = open(rd->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(rd->filename);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 stdout");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

// static int	apply_heredoc(t_redirection *rd)
// {
// 	int	fd;

// 	fd = open(rd->filename, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror(rd->filename);
// 		return (-1);
// 	}
// 	if (dup2(fd, STDIN_FILENO) < 0)
// 	{
// 		perror("dup2 heredoc");
// 		close(fd);
// 		return (-1);
// 	}
// 	close(fd);
// 	unlink(rd->filename); // delete temporary heredoc file safely
// 	return (0);
// }
static int	apply_heredoc(t_redirection *rd)
{
	int	fd;

	printf("[HD] apply_heredoc | filename='%s'\n", rd->filename);
	fd = open(rd->filename, O_RDONLY);
	if (fd < 0)
	{
		perror(rd->filename);
		return (-1);
	}
	printf("[HD] heredoc file opened OK\n");
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 heredoc");
		close(fd);
		return (-1);
	}
	printf("[HD] heredoc dup2 OK (STDIN replaced)\n");
	close(fd);
	unlink(rd->filename);
	printf("[HD] heredoc file unlinked\n");
	return (0);
}

int	apply_redirect(t_redirection *rd)
{
	if (!rd || !rd->filename)
		return (-1);
	if (rd->type == R_IN)
		return (apply_rd_in(rd));
	else if (rd->type == R_OUT)
		return (apply_rd_out(rd));
	else if (rd->type == R_APPEND)
		return (apply_rd_append(rd));
	else if (rd->type == R_HEREDOC)
		return (apply_heredoc(rd));
	ft_putstr_fd("minishell: unknown redirection type\n", 2);
	return (-1);
}
