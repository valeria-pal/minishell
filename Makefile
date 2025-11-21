CC = cc
CFLAGS = -Wall -Wextra -Werror
IFLAG =  -Iinclude
LDFLAGS = -lreadline
SRC =\
	SRCS := main.c \
        executor/execute_functions.c \
        executor/executor_utils.c \
        executor/execution/execution.c \
        executor/builtins/execute_builtins.c \
        executor/pipelines/pipeline_executor.c \
        executor/pipelines/error_checkers.c \
        executor/pipelines/pipes_utils.c \
        executor/redirections/redirection_application.c \
        executor/redirections/redirection_utils.c \
        signals/signals.c \
        string_utils/string_utils.c \
 
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