CC = cc
INC_DIR = inc
SRC_DIR = src
LIB_DIR = libs
OBJ_DIR = obj
BIN_DIR = bin
MAPS_DIR = maps
EXE = cub3d

MLX_INC = $(LIB_DIR)/mlx/inc
FTLIB_INC = $(LIB_DIR)/ftlib/inc
ifeq ($(UNAME_S), Darwin)
GLFW_LIB = -L /Users/$(USER)/brew/lib/libglfw3.a
endif 

MLX_LIB = $(LIB_DIR)/mlx/build/libmlx42.a
FT_LIB = $(LIB_DIR)/ftlib/bin/ftlib.a
FRAMEWORK = -O3 -ffast-math -framework Cocoa -framework OpenGL -framework IOKit -lglfw
ifeq ($(UNAME_S), Darwin)
    GLFW_INCLUDE = -I /Users/$(USER)/brew/Cellar/glfw/3.4/include/GLFW/glfw3.h
endif

LIBS = $(FRAMEWORK) $(FT_LIB) $(MLX_LIB) $(GLFW_LIB)
INCS = -I $(INC_DIR) -I $(FTLIB_INC) -I $(MLX_INC) $(GLFW_INCLUDE)
SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRCS:.c=.o))
NAME = $(BIN_DIR)/$(EXE)

ifeq ($(MAKECMDGOALS),debug)
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g -pthread
BUILDING_TYPE = debug
else
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g -pthread
BUILDING_TYPE = release
endif

all: build $(NAME)
# all: $(NAME)
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)
	@echo "-- Building executable done"
	@echo "-- Binary executable have been written to: $(PWD)/$(BIN_DIR)/$(EXE)"
ifeq ($(BUILDING_TYPE), release)
	@echo "-- Building in RELEASE mode"
endif

build:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)
ifeq ($(BUILDING_TYPE), debug)
	@cmake -DDEBUG=1 $(LIB_DIR)/mlx -B $(LIB_DIR)/mlx/build && make -C $(LIB_DIR)/mlx/build -j4
	@make debug -C $(LIB_DIR)/ftlib
else
	@cmake $(LIB_DIR)/mlx -B $(LIB_DIR)/mlx/build && make -C $(LIB_DIR)/mlx/build -j4
	@make -C $(LIB_DIR)/ftlib
endif

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/*.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@echo "-- Building executable : $@"
	@$(CC) $(OBJS) $(LIBS) -g -fsanitize=address -o $(NAME)

debug: all
	@echo "-- Building in DEBUG mode"

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIB_DIR)/ftlib

fclean:
	@rm -rf $(BIN_DIR)
	@rm -rf $(LIB_DIR)/mlx/build
	@make fclean -C $(LIB_DIR)/ftlib

re: fclean all

.PHONY: all, clean, fclean, re, build, debug,