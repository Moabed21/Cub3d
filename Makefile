NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror 
RM			= rm -rf
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
MLX_DIR		= minilibx-linux
MLX_LIB		= $(MLX_DIR)/libmlx_Linux.a
INCLUDES	= -I src/headers -I $(LIBFT_DIR) -I $(MLX_DIR)
MLX_FLAGS	= -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm
OBJ_DIR		= obj
SRC			= src/main.c \
			  src/map_parsing.c \
			  src/map_validation.c \
			  src/char_validation.c \
			  src/map_utils.c \
			  src/game_init.c \
			  src/execution.c \
			  src/render_utils.c \
			  src/render_wall.c \
			  src/move.c \
			  src/raycast.c \
			  src/error_handling.c \
			  src/mini_parse.c

OBJ			= $(SRC:src/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re