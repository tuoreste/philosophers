# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 14:23:29 by otuyishi          #+#    #+#              #
#    Updated: 2023/12/27 15:58:50 by otuyishi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Main Makefile
NAME = philo

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./includes -fsanitize=thread

# Source files
SRC_DIR = source
SRCS = $(addprefix $(SRC_DIR)/, \
main.c \
philosophers.c \
philo_assist.c \
philo_clean_args.c \
philo_monitor.c \
philo_split.c \
philo_todos.c \
philo_utils.c)

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(NAME)

# Compile the NAMEutable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compile individual source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the NAMEutable
fclean:
	rm -f $(OBJS) $(NAME)

clean:
	rm -f $(OBJS)

re: fclean all

# Phony targets
.PHONY: all fclean clean
