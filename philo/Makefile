SRCS =		parse_const.c \
            print.c \
			ft.c \
			handle_errors.c \
			forks.c \
			monitor.c \
			philosopher.c \
			time.c \
			main.c \
			death_checker.c \
			ft_more.c

SRCS_DIR = ./src

OBJS_DIR = ./obj

ALL_OBJS = $(SRCS:%.c=%.o)

FULLPATH_SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS = $(addprefix $(OBJS_DIR)/, $(ALL_OBJS))


NAME = philo

INCLUDES_DIR = includes
INCLUDES_FILES = \
	philosophers.h \
	libft.h

INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

FLAGS =	-Wall -Wextra -Werror -std=gnu99
PROFILER_FLAG =  -pg
CC = gcc

all: $(OBJS_DIR) $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) $(FLAGS) -lpthread -o $@

$(OBJS_DIR):
	/bin/mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES) | $(OBJS_DIR)
	$(CC) $(FLAGS) -I./$(INCLUDES_DIR) -c $< -o $@

clean:
	rm -rf obj*

fclean: clean
	rm -rf $(NAME)

re:		fclean all

.PHONY: all clean fclean re
