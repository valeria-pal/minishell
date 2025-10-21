CC = cc
CFLAGS = -Wall -Wextra -Werror
IFLAG =  -Iinclude
LDFLAGS = -lreadline
SRC = src/main.c \
	src/prompt.c \
	src/tokenizer.c \
	src/token_utils.c \
	src/executor/execute_function.c \
	src/executor/executor_utils.c \
	src/executor/utils/split.c \
	src/executor/utils/string_utils.c \
	src/executor/utils/utils.c \
	src/executor/signals/signals.c \
	src/executor/redirections/redirection_application.c \
	src/executor/redirections/redirection_utils.c

OBJ := $(SRC:.c=.o)

.PHONY: all clean fclean re

	  
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