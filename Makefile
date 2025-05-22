NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRC = philo.c utils.c init.c action.c fork_utils.c free.c thread_init.c waiter.c
OBJ = $(SRC:.c=.o)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
