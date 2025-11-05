/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:37:08 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/04 14:53:25 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// static char	*ft_strcon(char const *s1, char const *s2, char *ptr)
// {
// 	int		i;
// 	int		j;
// 	char	*p;

// 	p = ptr;
// 	i = 0;
// 	while (s1[i])
// 	{
// 		*p = s1[i];
// 		p++;
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j])
// 	{
// 		*p = s2[j];
// 		p++;
// 		j++;
// 	}
// 	*p = '\0';
// 	return (ptr);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*ptr;
// 	int		i;
// 	int		j;

// 	i = ft_strlen(s1);
// 	j = ft_strlen(s2);
// 	ptr = malloc(i + j + 1);
// 	if (ptr == NULL)
// 		return (NULL);
// 	return (ft_strcon(s1, s2, ptr));
// }
char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (s1[i])
		res[j++] = s1[i++];
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	return (res);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isalnum(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9'))
		return (1);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
