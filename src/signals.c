/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:23:47 by vpaliash          #+#    #+#             */
/*   Updated: 2025/11/23 19:42:40 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

volatile sig_atomic_t	g_sig = 0;

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sig = SIGINT;
		write(1, "\n", 1);
		rl_utils();
	}
	else if (signum == SIGQUIT)
	{
		(void)g_sig;
	}
}

void	setup_signals(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	rl_catch_signals = 0;
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_termios(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_lflag = term.c_lflag & ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
