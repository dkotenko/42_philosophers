SRCS =		check_input.c \
			print.c

SRCS_P1 = p1.c $(SRCS)
SRCS_P2 = p2.c $(SRCS)
SRCS_P3 = p3.c $(SRCS)

SRCS_DIR = ./SRC
OBJS_DIR_P1 = ./obj_p1
OBJS_DIR_P2 = ./obj_p2
OBJS_DIR_P3 = ./obj_p3

OBJS_P1 = $(SRCS_P1:%.c=%.o)
OBJS_P2 = $(SRCS_P2:%.c=%.o)
OBJS_P3 = $(SRCS_P3:%.c=%.o)

NAME_P1 = philo_one
NAME_P2 = philo_two
NAME_P3 = philo_three

INCLUDES_DIR = ./includes/
INCLUDES =	philosophers.h

FLAGS =		-Wall -Wextra -Werror

CC = gcc

all: 		$(NAME_P1) #$(NAME_P2) $(NAME_P3)

$(NAME_P1):	$(OBJS_P1)
			$(CC) $(OBJS_P1) $(FLAGS) -o $@

$(OBJS_DIR_P1):
	/bin/mkdir -p $(OBJS_DIR_P1)

$(OBJS_DIR_P1)/%.o: $(SRCS_P1)/%.c $(INCLUDES) | $(OBJS_DIR_P1)
	$(CC) $(FLAGS) -I./includes -c $< -o $@

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