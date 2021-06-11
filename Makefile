SRCS =		check_input.c \
			main.c


INCLUDES =	philosophers.h

NAME =		Weapon

FLAGS =		-Wall -Wextra -Werror

CC = gcc

all: 		$(NAME)

$(NAME):	$(INCLUDES) $(SRCS)
			$(CC) $(SRCS) $(FLAGS) -o $@

clean:
			@rm -rf *.o

fclean:		clean
			@rm -rf $(NAME)

re:			fclean all

.PHONY: 	all clean fclean re