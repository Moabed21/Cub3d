NAME = so_long

CC = cc
CFLAGS = -g -Werror -Wall -Wextra
INCLUDES = -I./ -I./libft -Iprintf -I./minilibx-linux

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

printf_DIR = ./printf
printf = $(printf_DIR)/libftprintf.a

SRC =	mapcheck/map_manager.c \
		mapcheck/calculate.c \
		mapcheck/wall_rect_reach.c \
		mapcheck/count_chars.c \
		mapcheck/read_file.c \
		render/set_values.c \
		render/move_and_render.c \
		render/main.c

OBJ =	$(SRC:.c=.o)

INC =	-I$(LIBFT_DIR) -I$(printf_DIR) -Iso_long_inc -Iminilibx-linux -Imapcheck -Irender

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	if [ -d $(MLX_DIR) ]; then \
		cd $(MLX_DIR); \
		git diff --quiet || git stash; \
		make; \
	else \
		git clone https://github.com/42paris/minilibx-linux.git $(MLX_DIR); \
		cd $(MLX_DIR); \
		make; \
	fi

$(LIBFT):
	@make -C $(LIBFT_DIR) full

$(printf):
	@make -C $(printf_DIR)

$(NAME): $(OBJ) $(LIBFT) $(printf) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT) $(printf) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean
	@make -C $(printf_DIR) clean
	if [ -d $(MLX_DIR) ]; then \
		make -C $(MLX_DIR) clean; \
	fi

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(printf_DIR)

re: fclean all

.PHONY: all clean fclean re