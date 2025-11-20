#ifndef EXECUTOR_H
# define EXECUTOR_H

// Standard C library
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// POSIX/Unix libraries
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

// Readline library
#include <readline/readline.h>
#include <readline/history.h>

// Tokens
typedef enum e_toktype
{

	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	EOL
}								t_toktype;

typedef struct s_token
{
	char *value; // NULL for EOL
	t_toktype					type;
	struct s_token				*next;
}								t_token;

// Parser
typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND, 
	R_HEREDOC
}								t_redir_type;

typedef struct s_redirection
{
	t_redir_type				type;
	char						*filename;
	struct s_redirection		*next;
}								t_redirection;

typedef struct s_command
{
	char **argv;            /* execve argv */
	t_redirection *redirs;  /* linked list of redirs */
	struct s_command *next; /* next in pipeline */
}								t_command;

// Global variable
extern volatile sig_atomic_t	g_sig;

// Executor API
char							*find_path(const char *cmd);
int								execute(t_command *cmd, char *const envp[]);

// Redirections
int								apply_redirect(t_redirection *rd);
int								apply_redirections_to_cmd(t_command *cmd);


// Utils
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	free_split(char **arr);
int	is_space(char c);
char	*dup_str(const char *s, size_t n);
void	*ft_memset(void *s, int value, size_t n);


// Signals and terminal settings
extern volatile sig_atomic_t	g_sig;
void							signal_handler(int signum);
void							setup_signals(void);
void							set_termios(void);


//Pipes
int	count_cmds(t_command *cmd);
void	close_pipes(int pipe_fds[][2], int pipe_count);
void	pipe_error_check(int pipe_fds[][2], int i);
int	(*create_pipes(t_command *cmd))[2];
pid_t	*allocate_pids(int cmd_count, int (*pipes)[2];);
void	execute_pipeline(t_command *cmd, char **envp)

// Prompt
void	prompt(void);

// Readline utils
void	rl_utils(void);

// Tokenizer
int					append_token(t_token **head, t_token **tail, t_token *node);
void				free_tokenlist(t_token *tok);
void				print_tokens(t_token *t);
void				tokenize_output(const char *line);

#endif