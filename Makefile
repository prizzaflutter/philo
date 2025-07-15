CC = cc 

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

NAME = philo

SRC = main.c ft_atoi.c utils.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) ${OBJ} -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -rf $(OBJ)

fclean: clean 
	rm -rf $(NAME)

re: fclean all
