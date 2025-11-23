/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:35:45 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/23 19:22:58 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

static int	find_length(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*reverse_str(int i, char *nb)
{
	int		j;
	int		k;
	char	temp;

	j = 0;
	k = i - 1;
	while (j < k)
	{
		temp = nb[j];
		nb[j] = nb[k];
		nb[k] = temp;
		j++;
		k--;
	}
	return (nb);
}

static char	*convert_to_string(char *nb, int i, int n, int sign)
{
	if (n == -2147483648)
	{
		nb[i] = '8';
		n = n / 10;
		i++;
	}
	if (n < 0)
		n *= -1;
	if (n == 0)
		nb[i++] = '0';
	nb[i] = '\0';
	while (n > 0)
	{
		nb[i] = n % 10 + '0';
		n /= 10;
		i++;
	}
	if (sign < 0)
		nb[i++] = '-';
	nb[i] = '\0';
	return (reverse_str(i, nb));
}

char	*ft_itoa(int n)
{
	char	*nb;
	int		i;
	int		str_size;
	int		sign;

	sign = n;
	i = 0;
	str_size = find_length(n);
	nb = malloc(str_size * sizeof(char) + 1);
	if (nb == NULL)
		return (NULL);
	return (convert_to_string(nb, i, n, sign));
}

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
