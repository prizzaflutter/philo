CC = cc 

CFLAGS = -Wall -Wextra -Werror

NAME = philo

SRC = main.c 

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
