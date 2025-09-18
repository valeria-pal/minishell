/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:23:47 by vpaliash          #+#    #+#             */
/*   Updated: 2025/09/18 21:25:46 by vpozniak         ###   ########.fr       */
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
		write(2, "\n", 1);
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
void	set_termios(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag = term.c_lflag & ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
