#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_cmd
{
	char			**args;
	struct s_cmd	*next;
}					t_cmd;

# include "minishell.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

// executor functions
char				*find_path(const char *cmd);
int					execute(t_cmd *cmd, char *const envp[]);

// string functions
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s);
char				*ft_strchr(const char *s, int c);
char				**ft_split(char const *s, char c);
char				*ft_strjoin(char const *s1, char const *s2);

// split functions
char				**ft_split(char const *s, char c);
void				free_split(char **arr);
#endif