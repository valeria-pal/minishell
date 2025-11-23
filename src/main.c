/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:13:18 by vpaliash          #+#    #+#             */
/*   Updated: 2025/11/23 19:42:53 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_bash	bash_struct;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("Incorrect arguments count!\n", 2), 1);
	bash_struct.envp = copy_env(envp);
	if (!bash_struct.envp)
		return (ft_putstr_fd("Failed to copy environment\n", 2), 1);
	bash_struct.last_exit_status = 0;
	set_termios();
	setup_signals();
	prompt(&bash_struct);
	free_env(bash_struct.envp);
	return (0);
}
