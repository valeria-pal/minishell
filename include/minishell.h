#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

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

t_token				*tokenize(const char *line);
int					is_space(char c);
char				*dup_str(const char *s, size_t n);
t_token				*new_token(char *value, t_toktype type);
int					append_token(t_token **head, t_token **tail, t_token *node);
int					add_word_token(const char *start, size_t len,
						t_token **head, t_token **tail);
int					add_eol_token(t_token **head, t_token **tail);
void				free_tokenlist(t_token *tok);
void				print_tokens(t_token *t);

#endif
