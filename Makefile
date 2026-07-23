NAME	= cub3D
CC		= cc
CFLAGS	= #-Wall -Wextra -Werror
RM		= rm -f

MLX_DIR		= src/headers/minilibx-linux
MLX_LIB		= $(MLX_DIR)/libmlx_Linux.a
INCLUDES	= -I src/headers -I $(MLX_DIR)
MLX_FLAGS	= -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

SRC		= src/main.c \
		  src/map_parsing.c \
		  src/map_validation.c \
		  src/char_validation.c \
		  src/map_utils.c \
		  src/ft_split.c \
		  src/game_init.c \
		  src/get_next_line.c \
		  src/get_next_line_utils.c
OBJ		= $(SRC:.c=.o)

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re