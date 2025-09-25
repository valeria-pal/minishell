#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

# define SQ 39
# define DQ 34
// Token types
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

// Token node
typedef struct s_token
{
	char *value; // NULL for EOL
	t_toktype					type;
	struct s_token				*next;
}								t_token;

// Parcer structs
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
		char **argv; //// int execve(const char *pathname, char *const argv[],char *const envp[]);
		t_redirection			*redirs;
		struct s_command		*next;
}								t_command;

// Utils
int								is_space(char c);
char							*dup_str(const char *s, size_t n);
void							*ft_memset(void *s, int value, size_t n);
char							*ft_strdup(const char *s1);
// Tokenizer
int								append_token(t_token **head, t_token **tail,
									t_token *node);
t_token							*new_token(char *value, t_toktype type);
int								add_eol_token(t_token **head, t_token **tail);
void							free_tokenlist(t_token *tok);
void							print_tokens(t_token *t);
void							tokenize_output(const char *line);
int								process_token(const char *line, int *i,
									t_token **head, t_token **tail);
int								skip_spaces(const char *line, int i);

// Parcer
t_redirection					*new_redirection(t_redir_type type,
									char *filename);
int								append_redirection(t_redirection **head,
									t_redirection *node);
void							free_redirections(t_redirection *head);
void							free_commands(t_command *cmd);
// t_command					*parse_command(t_token **tok_ptr);
t_command						*parse_pipeline(t_token *tokens);
t_command						*cmd_new(void);
void							print_commands(t_command *cmd);

// Signals and terminal settings
extern volatile sig_atomic_t	g_sig;
void							signal_handler(int signum);
void							setup_signals(void);
void							set_termios(void);
void							rl_utils(void);
void							prompt(void);

#endif
