CC = cc
#CFLAGS = -Wall -Wextra -Werror\
IFLAG =  -Iinclude\
LDFLAGS = -lreadline\#
CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

#executor/redirections/pipelines/pipes.c
SRC = src/main.c \
	  src/utils.c \
	  src/signals.c \
	  src/prompt.c \
	  executor/execute_function.c \
	  executor/executor_utils/executor_utils.c \
	  executor/redirections/redirection_application.c \
	  executor/redirections/redirection_utils.c \
	  tokenizer/token_utils.c \
	  tokenizer/tokenizer.c \
	  tokenizer/token_utils1.c\
	  tokenizer/debug.c\
	  parcer/parcer.c\
	  parcer/debug.c\
	  parcer/par_utils.c\
	  parcer/quotes_and_expand.c\
	  parcer/parse_1cm_utils.c\
	  parcer/syntax_errors.c\
	  parcer/heredoc.c\
	  libft/libft_utils1.c\
	  libft/libft_utils2.c\
	  libft/libft_itoa.c\
	  libft/libft_utils3.c\
	  libft/libft_split.c\
	  expander/exp_utils.c\


OBJ = $(SRC:.c=.o)
NAME = minishell
RM = rm -f

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)


clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all