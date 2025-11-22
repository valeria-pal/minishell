/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:40:32 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/15 12:04:52 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	rl_utils(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
