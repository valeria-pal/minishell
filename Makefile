CC = cc
CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline
SRC = src/main.c \
	  src/utils.c \
	  src/tokenizer.c \
	  src/signals.c \
	  src/prompt.c \
	  src/token_utils.c \


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