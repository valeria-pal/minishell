CC = cc
CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline
SRC = src/main.c \
	  src/utils.c \
	  src/signals.c \
	  src/prompt.c \
	  tokenizer/token_utils.c \
	  tokenizer/tokenizer.c \
	  tokenizer/debug.c\
	  parcer/parcer.c\
	  parcer/debug.c\
	  parcer/par_utils.c


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