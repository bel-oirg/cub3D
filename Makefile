CC = cc
NAME = cub3D  
GLFLAGS = -ffast-math -framework Cocoa -framework OpenGL -framework IOKit -lglfw# -fsanitize=address 
# CFLAGS =  
RM = rm -rf

SRCS = cub_raw.c main.c move_player.c wall_render.c

OBJS = $(SRCS:.c=.o)
HEADER = cub.h

all : $(NAME)

$(NAME) : $(OBJS) 
	$(CC) $(GLFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(GLFLAGS) -c $< -o $@

$(OBJS) : $(HEADER)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(OBJS)

re : fclean all

.PHONY: all clean fclean re