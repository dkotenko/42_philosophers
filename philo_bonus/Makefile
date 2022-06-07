SRCS =		parse_arguments.c \
            print.c \
			ft.c \
			handle_errors.c
			
SRCS_P1 = $(SRCS)
SRCS_P1 += p1.c
SRCS_P2 = $(SRCS)
SRCS_P2 += p2.c
SRCS_P3 = $(SRCS)
SRCS_P3 += p3.c

SRCS_DIR = ./src
OBJS_DIR_P1 = ./obj_p1
OBJS_DIR_P2 = ./obj_p2
OBJS_DIR_P3 = ./obj_p3

ALL_OBJS_P1 = $(SRCS_P1:%.c=%.o)
ALL_OBJS_P2 = $(SRCS_P2:%.c=%.o)
ALL_OBJS_P3 = $(SRCS_P3:%.c=%.o)

FULLPATH_SRCS_P1 = $(addprefix $(SRCS_DIR)/, $(SRCS_P1))
FULLPATH_SRCS_P2 = $(addprefix $(SRCS_DIR)/, $(SRCS_P2))
FULLPATH_SRCS_P3 = $(addprefix $(SRCS_DIR)/, $(SRCS_P3))

OBJS_P1 = $(addprefix $(OBJS_DIR_P1)/, $(ALL_OBJS_P1))
OBJS_P2 = $(addprefix $(OBJS_DIR_P2)/, $(ALL_OBJS_P2))
OBJS_P3 = $(addprefix $(OBJS_DIR_P3)/, $(ALL_OBJS_P3))


NAME_P1 = philo_one
NAME_P2 = philo_two
NAME_P3 = philo_bonus

INCLUDES_DIR = includes
INCLUDES =	$(INCLUDES_DIR)/philosophers.h

FLAGS =	-Wall -Wextra -Werror

CC = gcc

all: $(OBJS_DIR_P3) $(NAME_P3)

$(NAME_P3):	$(OBJS_P3)
	$(CC) $(OBJS_P3) $(FLAGS) -lpthread -o $@

$(OBJS_DIR_P3):
	/bin/mkdir -p $(OBJS_DIR_P3)

$(OBJS_DIR_P3)/%.o: $(SRCS_DIR)/%.c $(INCLUDES) | $(OBJS_DIR_P3)
	$(CC) $(FLAGS) -I./$(INCLUDES_DIR) -c $< -o $@

clean:
	@rm -rf obj_*

fclean: clean
	@rm -rf $(NAME_P1) $(NAME_P2) $(NAME_P3)

re:		fclean all

.PHONY: all clean fclean re
