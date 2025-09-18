/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:40:32 by vpozniak          #+#    #+#             */
/*   Updated: 2025/09/18 21:26:01 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

void	*ft_memset(void *s, int value, size_t n)
{
	size_t			i;
	unsigned char	*arr;

	i = 0;
	arr = (unsigned char *)s;
	while (i < n)
	{
		arr[i] = (unsigned char)value;
		i++;
	}
	return (s);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

char	*dup_str(const char *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(n + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[n] = '\0';
	return (str);
}
void	rl_utils(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
