/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 19:42:23 by vpozniak          #+#    #+#             */
/*   Updated: 2025/11/17 22:45:02 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Standard C library
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

// POSIX/Unix libraries
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

// Readline library
# include <readline/history.h>
# include <readline/readline.h>

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
	char						*value;
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

typedef struct s_bash
{
	int							last_exit_status;
	char						**envp;
}								t_bash;

typedef struct s_command
{
	char						**argv;
	t_redirection				*redirs;
	struct s_command			*next;
}								t_command;

// Utils
int								is_space(char c);
char							**ft_split(char const *s, char c);
char							*ft_strchr(const char *s, int c);
void							free_split(char **arr);
void							*ft_memset(void *s, int value, size_t n);
char							*ft_strdup(const char *s1);
char							*ft_strndup(const char *s1, size_t n);
size_t							ft_strlen(const char *s);
char							*ft_strjoin(char const *s1, char const *s2);
int								ft_isalpha(int c);
int								ft_isalnum(char c);
void							ft_putstr_fd(char *s, int fd);
char							*ft_itoa(int num);
int								ft_strncmp(const char *s1, const char *s2,
									size_t n);
int								ft_strcmp(char *s1, char *s2);

// Executor API
char							*find_path(const char *cmd);
int								execute(t_command *cmd, t_bash *bash_struct);

// Redirections
int								apply_redirect(t_redirection *rd);
int								apply_redirections_to_cmd(t_command *cmd);
int								apply_all_redirections(t_command *head);

// Tokenizer
int								append_token(t_token **head, t_token **tail,
									t_token *node);
t_token							*new_token(char *value, t_toktype type);
int								add_eol_token(t_token **head, t_token **tail);
void							free_tokenlist(t_token *tok);
void							print_tokens(t_token *t);
void							tokenize_output(const char *line,
									t_bash *bash_struct);
int								process_token(const char *line, int *i,
									t_token **head, t_token **tail);
int								skip_spaces(const char *line, int i);
t_toktype						get_operator_type(const char *s, int *len);

// Syntax check

// Parcer
t_redirection					*new_redirection(t_redir_type type,
									char *filename);
int								append_redirection(t_redirection **head,
									t_redirection *node);
void							free_redirections(t_redirection *head);
void							free_commands(t_command *cmd);
t_command						*parse_pipeline(t_token *tokens,
									t_bash *bash_struct);
t_command						*cmd_new(void);
void							print_commands(t_command *cmd);
char							*expand_variable(char *string,
									t_bash *bash_struct);
char							*strip_double_quotes_and_expand(char *str,
									t_bash *bash_struct);
char							*strip_single_quotes(char *str);
int								has_dollar(char *str);
int								check_syntax_errors(t_token *tokens);
t_command						*parse_one_command(t_token **tok_ptr,
									t_bash *bash_struct);
char							*normalize_word(char *original_word,
									t_bash *bash_struct);
int								count_args_until_pipe(t_token *tok);
int								add_redirection(t_command *cmd,
									t_token **tok_ptr);
int								add_heredoc_redir(t_command *cmd,
									t_token **tok_ptr);
void							child_heredoc(char *delimiter, int fd);
int								parent_heredoc(pid_t pid, int fd);
int								heredoc_create(char *delimiter, char *outfile);

// Expander
char *my_getenv(t_bash *bash_struct, const char *name);

// Signals and terminal settings
extern volatile sig_atomic_t	g_sig;
void							signal_handler(int signum);
void							setup_signals(void);
void							set_termios(void);
void							rl_utils(void);
void							prompt(t_bash *bash_struct);

#endif
