#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/01 18:17:13 by lfaria-m          #+#    #+#              #
#    Updated: 2024/12/25 17:01:12 by lfaria-m         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# Program name
NAME = philo

# Directories
SRC_DIR = srcs
OBJ_DIR = objs

# Source files (explicitly listed)
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/init_sim.c $(SRC_DIR)/utils.c $(SRC_DIR)/sim.c $(SRC_DIR)/sleep_think.c
       

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -fsanitize=address -Werror

# To link readline
RD = -lreadline -lncurses
# Libraries


# Tools
AR = ar rcs
RM = rm -f

# Build rules
all: $(NAME)

# Link the final program
$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -lpthread $(RD) -o $(NAME)

# Compile source files to object files in the objs directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure the objs directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build Libft if not already built


# Clean up object files
clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJ_DIR)
	

# Clean up everything, including the executable
fclean: clean
	$(RM) $(NAME)

# Rebuild the project
re: fclean all

.PHONY: all clean fclean re
