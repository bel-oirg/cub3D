NAME = cub3d
BONUS_NAME = cub3d_bonus
CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address

OBJ_DIR = obj
SRC_DIR = mandatory

HEADER = ./inc/cub.h
HEADER_BONUS = ./inc/cub_bonus.h

MAN_FILES = create_data.c cub.c elems.c raycasting.c\
			file_reading.c ft_split.c ft_split2.c ft_str_1.c \
			ft_str_2.c gnl.c main.c parser.c player_mv.c\
			rendering.c verify.c raycast_calc.c utils.c my_malloc.c \
			rendering_helper.c

BONUS_FILES =  create_data.c cub.c elems.c raycasting.c\
			file_reading.c ft_split.c ft_split2.c ft_str_1.c \
			ft_str_2.c gnl.c main.c parser.c player_mv.c\
			rendering.c verify.c raycast_calc.c utils.c\
			my_malloc.c sprite.c mini_map.c ft_itoa.c\
			rendering_helper.c

OBJ_MAN = $(patsubst %.c, obj/mandatory/%.o, $(MAN_FILES))
OBJ_BON = $(patsubst %.c, obj/bonus/%.o, $(BONUS_FILES))

CFLAGS = $(FLAGS) -c

LDFLAGS = $(FLAGS)

MLX_LIB = ./inc/libmlx42.a
GLFW_LIB = ./inc/libglfw3.a
FRAMEWORK =  $(MLX_LIB) $(GLFW_LIB) -O3 -g -ffast-math -framework Cocoa -framework OpenGL -framework IOKit# -lglfw3

all : $(OBJ_DIR) $(NAME) 

$(NAME) : $(OBJ_MAN)
	$(CC) $(LDFLAGS) $(FRAMEWORK) $^ -o $@

bonus : $(OBJ_DIR_BONUS) $(BONUS_NAME) ./inc/cub_bonus.h

$(BONUS_NAME) : $(OBJ_BON) 
	$(CC) $(LDFLAGS) $(FRAMEWORK) $^ -o $(BONUS_NAME)

obj/mandatory/%.o: mandatory/%.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

obj/bonus/%.o: bonus/%.c $(HEADER_BONUS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR) :
	mkdir -p obj/mandatory
	mkdir -p obj/bonus

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus