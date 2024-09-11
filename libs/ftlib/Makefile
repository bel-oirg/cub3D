# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 17:14:02 by aelmrabe          #+#    #+#              #
#    Updated: 2024/04/27 13:47:11 by aelmrabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
INC_DIR = inc
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
EXE = ftlib.a

SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRCS:.c=.o))
NAME = $(BIN_DIR)/$(EXE)
	
# ifeq ($(MAKECMDGOALS),debug)
# 	CFLAGS = -g
# else
CFLAGS = -Wall -Wextra -Werror
# endif

all: build $(NAME)
	@echo "-- Building FTLIB done"
	@echo "-- Lib archive have been written to: $(PWD)/$(BIN_DIR)/$(EXE)"

debug: all

build:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/*.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@echo "-- Building static library: $@"
	@ar rcs $@ $(OBJS)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(BIN_DIR)

re: fclean all

.PHONY: all, clean, fclean, re, build, debug