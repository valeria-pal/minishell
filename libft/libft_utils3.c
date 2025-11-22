/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:36:39 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/15 12:04:12 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_copy;
	unsigned char	*s2_copy;

	s1_copy = (unsigned char *)s1;
	s2_copy = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (s1_copy[i] && s2_copy[i] && i < n)
	{
		if (s1_copy[i] < s2_copy[i])
			return (s1_copy[i] - s2_copy[i]);
		else if (s1_copy[i] > s2_copy[i])
			return (s1_copy[i] - s2_copy[i]);
		i++;
	}
	if (i < n)
		return (s1_copy[i] - s2_copy[i]);
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
