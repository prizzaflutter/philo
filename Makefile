CC = cc 

CFLAGS = -Wall -Wextra -Werror # -g3 -fsanitize=address

NAME = philo

SRC = main.c ft_atoi.c utils.c philo_routine.c print_mutex.c

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
