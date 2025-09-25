/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpaliash <vpaliash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:46:00 by vpaliash          #+#    #+#             */
/*   Updated: 2025/09/25 16:29:06 by vpaliash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_size;

	i = 0;
	src_size = ft_strlen(src);
	if (size == 0)
		return (src_size);
	while ((i < size - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	return (src_size);
}

static int	ft_count_tokens(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

void	free_split(char **arr)
{
	char	**start;

	if (!arr)
		return ;
	start = arr;
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(start);
}

static char	**fill_tokens(const char *s, char c, char **arr)
{
	const char	*start;
	int		i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			start = (char *)s;
			while (*s && *s != c)
				s++;
			arr[i] = (char *)malloc((s - start + 1) * sizeof(char));
			if (!arr[i])
			{
				arr[i] = NULL;
				return (free_split(arr), NULL);
			}
			ft_strlcpy(arr[i], start, s - start + 1);
			i++;
		}
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		token_count;
	char	**arr;

	if (!s)
		return (NULL);
	token_count = ft_count_tokens(s, c);
	arr = (char **)malloc((token_count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (!fill_tokens(s, c, arr))
		return (NULL);
	return (arr);
}
