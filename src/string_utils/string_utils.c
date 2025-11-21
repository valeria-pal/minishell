/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:05:14 by vpaliash          #+#    #+#             */
/*   Updated: 2025/11/20 23:35:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"


int ft_strcmp(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2)
        str1++, str2++;
    return (*str1 - *str2);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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
char	*ft_strdup(const char *s)
{
	int		size;
	char	*arr;
	char	*start;

	size = ft_strlen(s);
	arr = (char *)malloc((size + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	start = arr;
	while (*s)
	{
		*arr = *s;
		arr++;
		s++;
	}
	*arr = '\0';
	return (start);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t s1_size;
	size_t s2_size;
	size_t i;
	char *arr;

	i = 0;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	arr = (char *)malloc((s1_size + s2_size + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	while (*s1)
	{
		arr[i++] = *s1;
		s1++;
	}
	while (*s2)
	{
		arr[i++] = *s2;
		s2++;
	}
	arr[i] = '\0';
	return (arr);
}