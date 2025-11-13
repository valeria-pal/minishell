#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

typedef struct s_bash
{
	int		last_exit_status;
	char	**envp;
}			t_bash;

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*s2;
	size_t	i;

	i = 0;
	s2 = (char *)malloc(sizeof(char) * (n + 1));
	if (!s2)
		return (NULL);
	while (s1[i] && i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

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

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	char	*p;
	int		i;

	ptr = malloc(ft_strlen(s1) + 1);
	if (ptr == NULL)
		return (NULL);
	p = ptr;
	i = 0;
	while (s1[i])
	{
		*p = s1[i];
		p++;
		i++;
	}
	*p = '\0';
	return (ptr);
}

static int	count_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int num)
{
	char		*dst;
	int			count;
	int			i;
	long int	n;

	n = num;
	count = count_size(n);
	i = 0;
	if (n < 0 || count == 0)
		count++;
	if (!(dst = (char *)malloc((count + 1) * sizeof(char))))
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		dst[0] = '-';
		i++;
	}
	while (count > i)
	{
		count--;
		dst[count] = (n % 10) + '0';
		n /= 10;
	}
	return (dst);
}
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

char	*my_getenv(t_bash *bash_struct, const char *name)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (bash_struct->envp[i])
	{
		if (ft_strncmp(bash_struct->envp[i], name, len) == 0
			&& bash_struct->envp[i][len] == '=')
			return (bash_struct->envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*append_char(char *result, char c)
{
	char	tmp[2];
	char	*new;

	tmp[0] = c;
	tmp[1] = '\0';
	new = ft_strjoin(result, tmp);
	free(result);
	return (new);
}

static char	*append_var_value(char *str, int *i, char *result,
		t_bash *bash_struct)
{
	int		start;
	char	*var_name;
	char	*value;
	char	*tmp;

	start = *i;
	while (str[*i] && str[*i]!= 32)
		(*i)++;
	var_name = ft_strndup(str + start, *i - start);
	value = my_getenv(bash_struct, var_name);
	free(var_name);
	if (!value)
		return (result);
	tmp = ft_strjoin(result, value);
	free(result);
	return (tmp);
}
static char	*qmark_gv(char *result, t_bash *bash_struct, int *i)
{
	char	*temp;
	char	*exit_status;

	exit_status = ft_itoa(bash_struct->last_exit_status);
	temp = ft_strjoin(result, exit_status); // free temp??
	free(exit_status);
	result = temp;
	(*i)++;
	return (result);
}

char	*expand_variable(char *str, t_bash *bash_struct)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
				result = qmark_gv(result, bash_struct, &i);
			else if (str[i])
				result = append_var_value(str, &i, result, bash_struct);
			else
				result = append_char(result, '$');
		}
		else
			result = append_char(result, str[i++]);
	}
	return (result); // have to free later
}

int	main(int argc, char **argv, char **envp)
{
	t_bash	bash_struct;
	char	*result;
	char	*str2;
	char	*str3;

	// char	*str;
	char	*str1;
	(void)argv;
	bash_struct.envp = envp;
	bash_struct.last_exit_status = -1;
	// str = "Hello$?";
	str1 = "$?  HELLO";
	str2 = "$?  HELLO $USER";
	str3 = "$?  HELLO $? LOL provokacja $USER $? $USER. alallalallalla $USER $? ";
	result = expand_variable(str3, &bash_struct);
	printf("%s", result);
	return (0);
}
