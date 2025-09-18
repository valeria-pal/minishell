/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:40:27 by vpozniak          #+#    #+#             */
/*   Updated: 2025/09/18 21:16:32 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// Utils
int								is_space(char c);
char							*dup_str(const char *s, size_t n);
void							*ft_memset(void *s, int value, size_t n);

// Tokenizer
int								append_token(t_token **head, t_token **tail,
									t_token *node);
t_token							*new_token(char *value, t_toktype type);
int								add_eol_token(t_token **head, t_token **tail);
void							free_tokenlist(t_token *tok);
void							print_tokens(t_token *t);
void							tokenize_output(const char *line);

// Signals and terminal settings
extern volatile sig_atomic_t	g_sig;
void							signal_handler(int signum);
void							setup_signals(void);
void							set_termios(void);
void							rl_utils(void);
void							prompt(void);

#endif