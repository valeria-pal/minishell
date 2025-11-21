#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# include <readline/readline.h>
# include <readline/history.h>

//tookens

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
	char			*value;
	t_toktype		type;
	struct s_token	*next;
}	t_token;

//redirections

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

typedef struct s_redirection
{
	t_redir_type			type;
	char					*filename;
	struct s_redirection	*next;
}	t_redirection;

//commands

typedef struct s_command
{
	char				**argv;
	t_redirection		*redirs;
	struct s_command	*next;
}	t_command;

//bash state

typedef struct s_bash
{
	int		last_exit_status;
	char	**envp;
}	t_bash;

//global signal flag

extern volatile sig_atomic_t	g_sig;

//path

char	*find_path(const char *cmd);

//builtins

int		exec_builtin(t_command *cmd, t_bash *bash);

//redirections

int		apply_redirect(t_redirection *rd);
int		apply_redirections_to_cmd(t_command *cmd);

//execution

int		decode_errors(int status);
void	execute_one_cmd(t_command *cmd, t_bash *bash);
void	execute_pipeline(t_command *cmd, t_bash *bash);
void	execute(t_command *cmd, t_bash *bash);

//utils

char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	free_split(char **arr);
int		is_space(char c);
char	*dup_str(const char *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);

//signals and termios

void	signal_handler(int signum);
void	setup_signals(void);
void	setup_child_signals(void);
void	set_termios(void);

//pipes

int		count_cmds(t_command *cmd);
void	close_pipes(int pipe_fds[][2], int pipe_count);
void	pipe_error_check(int pipe_fds[][2], int i);
void errno_checker();
void check_fork_error(pid_t pid);
void handle_redirections_or_exit(t_command *cmd, char *path);
int		(*create_pipes(t_command *cmd))[2];
pid_t	*allocate_pids(int cmd_count, int (*pipes)[2]);

//readline utils

void	rl_utils(void);

//tokenizer utils

int		append_token(t_token **head, t_token **tail, t_token *node);
void	free_tokenlist(t_token *tok);
void	print_tokens(t_token *t);
void	tokenize_output(const char *line);

#endif
