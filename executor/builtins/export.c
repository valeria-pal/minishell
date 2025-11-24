/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:46:57 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/24 17:06:18 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../include/minishell.h"

int	builtin_export(char **argv, char ***envp)
{
	int	i;
	int	status;

	if (!argv[1])
	{
		print_all_exports(*envp);
		return (0);
	}
	status = 0;
	i = 1;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else if (update_env_var(envp, argv[i]) < 0)
			return (1);
		i++;
	}
	return (status);
}
