/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:13:18 by vpaliash          #+#    #+#             */
/*   Updated: 2025/09/18 21:26:34 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

// command to check: ls -l "    &USER" | >>          grep foo > <<out.txt
int	main(void)
{
	set_termios();
	setup_signals();
	prompt();
	return (0);
}
