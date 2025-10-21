#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

//Tokens
typedef enum e_toktype
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	EOL
}	t_toktype;

typedef struct s_token
{
	char			*value; //NULL for EOL 
	t_toktype		type;
	struct s_token	*next;
}	t_token;

//Parser
typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

typedef struct s_redirection
{
	t_redir_type				type;
	char						*filename;
	struct s_redirection		*next;
}	t_redirection;

typedef struct s_command
{
	char					**argv;    /* execve argv */
	t_redirection			*redirs;   /* linked list of redirs */
	struct s_command		*next;     /* next in pipeline */
}	t_command;

// Executor API
char	*find_path(const char *cmd);
int		execute(t_command *cmd, char *const envp[]);

//Redirections 
int		apply_redirect(const t_redirection *rd);
int apply_redirections_to_cmd(t_command *cmd);
int		apply_redirections_to_cmd(const t_command *cmd);

//Utils
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	free_split(char **arr);

//Utils
void	setup_signals_interactive(void);
void	setup_signals_child(void);

#endif