CC = cc
CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

#CFLAGS = -Wall -Wextra -Werror
#IFLAG =  -Iinclude
#LDFLAGS = -lreadline
#executor/builtins/execute_builtins.c
SRC = src/main.c \
	  src/utils.c \
	  src/env_utils.c \
	  src/signals.c \
	  src/prompt.c \
	  executor/builtins/cd.c\
	  executor/builtins/echo.c\
	  executor/builtins/env.c\
	  executor/builtins/exit.c\
	  executor/builtins/pwd.c\
	  executor/builtins/unset.c\
	  executor/builtins/export.c\
	  executor/builtins/export_utils.c\
	  executor/builtins/execute_builtins.c\
	  executor/execution/execute_function.c \
      executor/execution/executor_utils.c \
      executor/pipelines/pipeline_execution.c \
      executor/pipelines/error_checkers.c \
      executor/pipelines/pipes_utils.c \
      executor/redirections/redirection_application.c \
      executor/redirections/redirection_utils.c \
	  tokenizer/token_utils.c \
	  tokenizer/tokenizer.c \
	  tokenizer/token_utils1.c\
	  parcer/parcer.c\
	  parcer/par_utils.c\
	  parcer/quotes_and_expand.c\
	  parcer/parse_1cm_utils.c\
	  parcer/heredoc.c\
	  expander/exp_utils.c\
	  parcer/syntax_errors.c\
	  libft/libft_utils1.c\
	  libft/libft_utils2.c\
	  libft/libft_utils3.c\
	  libft/libft_utils4.c\
	  libft/ft_split.c\

OBJ = $(SRC:.c=.o)
NAME = minishell
RM = rm -f

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(IFLAG) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(IFLAG) $(OBJ) -o $(NAME) $(LDFLAGS)


clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re