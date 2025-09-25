CC = cc
CFLAGS = -Wall -Wextra -Werror
IFLAG =  -Iinclude
LDFLAGS = -lreadline
SRC = src/main.c \
	  src/utils.c \
	  src/tokenizer.c \
	  src/signals.c \
	  src/prompt.c \
	  src/token_utils.c \
	  src/string_utils.c\
	  src/executor/executor_utils.c\
	  src/executor/split.c \
	  src/executor/execute_function.c \

	  
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