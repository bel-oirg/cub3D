NAME = cub3d
CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
OBJ_DIR = obj
SRC_DIR = src

SRC_FILES = clear_data.c create_data.c cub.c elems.c raycasting.c\
			file_reading.c ft_split.c ft_split2.c ft_str_1.c \
			ft_str_2.c gnl.c main.c parser.c player_mv.c\
			rendering.c verify.c ft_itoa.c sprite.c mini_map.c

OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

CFLAGS = $(FLAGS) -c

LDFLAGS = $(FLAGS)

all:$(NAME)

MLX_LIB = ./inc/libmlx42.a
GLFW_LIB = ./inc/libglfw3.a
FRAMEWORK =  $(MLX_LIB) $(GLFW_LIB) -O3 -ffast-math -framework Cocoa -framework OpenGL -framework IOKit -lglfw3

$(NAME): $(MLX) $(OBJ_FILES)
	$(CC) $(LDFLAGS) $(FRAMEWORK) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re