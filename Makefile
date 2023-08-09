NAME = philo
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf
SRC      :=	philo.c

OBJ = $(SRC:.c=.o)

all: $(NAME) philo.h
$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:	
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
