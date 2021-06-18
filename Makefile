SRCS =		check_input.c \
			print.c \
			ft_strjoin.c

SRCS_P1 = main.c

SRCS_P2 = main.c

SRCS_P3 = main.c

P1_DIR = ./philo_one/
P2_DIR = ./philo_two/
P3_DIR = ./philo_three/
SRCS_DIR = ./SRC/

INCLUDES_DIR = ./includes/
INCLUDES =	philosophers.h

NAME_P1 = philo_one
NAME_P2 = philo_two
NAME_P3 = philo_three

FLAGS =		-Wall -Wextra -Werror

CC = gcc

all: 		$(NAME_P1) $(NAME_P2) $(NAME_P3)

$(NAME_P1):	$(INCLUDES) $(SRCS)
			$(CC) $(SRCS) $(FLAGS) -o $@

$(NAME_P2):	$(INCLUDES) $(SRCS)
			$(CC) $(SRCS) $(FLAGS) -o $@

$(NAME_P3):	$(INCLUDES) $(SRCS)
			$(CC) $(SRCS) $(FLAGS) -o $@

clean:
			@rm -rf *.o

fclean:		clean
			@rm -rf $(NAME_P1) $(NAME_P2) $(NAME_P3)

re:			fclean all

.PHONY: 	all clean fclean re