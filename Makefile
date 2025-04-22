NAME = philo

SRC = ft_utils_libft.c ft_utils.c ft_init.c ft_lock.c main.c
CC = cc -pthread -Wall -Werror -Wextra -g3
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)


.c.o:
		$(CC) -c $< -o $(<:.c=.o)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
