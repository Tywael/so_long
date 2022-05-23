CC 			= clang
MLX_LINUX = ./mlx-linux/
MLX_MAC = ./mlx/
OS_NAME = $(shell uname -s)
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g
INCLUDES 	= -I ./src/ -Imlx
OPTIONS 	= 
NAME		= so_long

FOLDER = src/

SRCS	= main.c\
		  read_map.c\
		  utils.c\
		  init.c\
		  gnl.c\
		  ft_realloc.c\
		  map_checker.c\
		  map_checker2.c\
		  utils2.c\
		  hook.c\
		  itoa.c\
		  hook_monster.c\
		  init_map.c\

SOURCES =  $(addprefix $(FOLDER), $(SRCS))

ifeq ($(OS_NAME), Linux)
	MLX_IS = $(MLX_LINUX)
	INCLUDES += -I $(MLX_LINUX)
	OPTIONS += -L $(MLX_LINUX) -lmlx -lXext -lX11
endif
ifeq ($(OS_NAME), Darwin)
	MLX_IS = $(MLX_MAC)
	INCLUDES += -I $(MLX_MAC)
	OPTIONS += -L $(MLX_MAC) -lmlx -framework OpenGL -framework Appkit
endif

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME) $(OPTIONS)
	
.c.o:
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
