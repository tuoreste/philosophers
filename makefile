# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 14:23:29 by otuyishi          #+#    #+#              #
#    Updated: 2023/11/27 16:44:28 by otuyishi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Main Makefile
NAME = philosophers

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

# Source files
SRCS = philosophers.c philo_utils.c

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
