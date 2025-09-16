/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaliash <vpaliash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:29:56 by vpaliash          #+#    #+#             */
/*   Updated: 2025/09/16 10:39:53 by vpaliash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_memset(void *s, int value, size_t n)
{
	size_t i;
	unsigned char *arr;

	i = 0;
	arr = (unsigned char *)s;
	while (i < n)
	{
		arr[i] = (unsigned char)value;
		i++;
	}
	return (s);
}