CC 			= gcc
CFLAGS		= -Wall -Wextra -Werror -Imlx -fsanitize=address -g
OPTIONS 	= -Lmlx -lmlx -lz -framework OpenGL -framework AppKit
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

OBJECTS = $(SOURCES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OPTIONS) -o $(NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
	rm -f $(OBJECTS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
