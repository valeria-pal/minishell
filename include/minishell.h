#ifndef MINISHELL_H
# define MINISHELL_H


# include <stddef.h>
# include <readline/history.h>
# include <readline/readline.h>

# include <stdio.h>
# include <stdlib.h>

#include <signal.h>
#include <termios.h>
#include <unistd.h>

// Token types
typedef enum e_toktype
{
	WORD,
	EOL
}					t_toktype;

// Token node
typedef struct s_token
{
	char *value; // NULL for EOL
	t_toktype		type;
	struct s_token	*next;
}					t_token;

// Utils
int					is_space(char c);
char				*dup_str(const char *s, size_t n);
void				*ft_memset(void *s, int value, size_t n);

// Tokenizer
int					append_token(t_token **head, t_token **tail, t_token *node);
void				free_tokenlist(t_token *tok);
void				print_tokens(t_token *t);
void				tokenize_output(const char *line);

void	rl_utils(void);

// Signals and terminal settings
extern volatile sig_atomic_t	g_sig;
void	signal_handler(int signum);
void setup_signals(void);
void set_termios(void);

void	prompt(void);

#endif
