/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:20:51 by moabed            #+#    #+#             */
/*   Updated: 2026/08/12 12:18:27 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../../libft/libft.h"
# include "../../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* ---- Key Codes ---- */
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define WIDTH 1920
# define HEIGHT 1080
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define TEX_SIZE 64

/* ---- Error Codes ---- */
typedef enum e_err_code
{
	ERR_NONE = 0,
	ERR_ARG_COUNT,
	ERR_FILE_EXT,
	ERR_FILE_OPEN,
	ERR_MALLOC,
	ERR_EMPTY,
	ERR_DUPLICATE_ELEMENT,
	ERR_MISSING_REQUIREMENTS,
	ERR_COLOR_RANGE,
	ERR_MAP_CONTENT,
	ERR_PLAYER_COUNT,
	ERR_MAP_OPEN,
	ERR_MLX_INIT,
	ERR_MLX_WIN
}				t_err_code;

/* ---- Structs ---- */

typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			tex_width;
	int			tex_height;
}				t_img;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_mlx
{
	void		*connection;
	void		*window;
	t_img		img;
	t_img		walls[4];

}				t_mlx;

typedef struct s_vec
{
	double		x;
	double		y;
}				t_vec;

typedef struct s_ray
{
	int			f_rgb[3];
	int			c_rgb[3];
	char		direction;
	t_vec		plane;
	t_vec		pos;
	t_vec		dir;
	t_point		int_position;
}				t_ray;

typedef struct s_raycast
{
	double		camera_x;
	t_vec		ray_dir;
	t_vec		delta_dist;
	t_vec		side_dist;
	t_point		step;
	t_point		map;
	int			hit;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	double		tex_pos;
	double		tex_step;
}				t_raycast;

typedef struct s_cub
{
	t_ray		exec;
	t_mlx		mlx_ops;
	t_raycast	raycast;
	t_err_code	err_code;
	char		*n_side;
	char		*s_side;
	char		*e_side;
	char		*w_side;
	char		*ceiling;
	char		*floor;
	char		*lines;
	char		**temp_sep_line;
	char		**map;
	char		**splitted_lines;
	int			data_count;
}				t_cub;

/* ---- Error Handling & Cub Init ---- */
void			initiate_cub(t_cub *cub);
void			free_cub(t_cub *cub);
void			handle_exit(t_cub *cub, t_err_code err_code, int exit_code);
char			*get_parsing_err_msg(t_err_code code);
char			*get_exec_err_msg(t_err_code code);
char			*get_error_msg(t_err_code code);
void			mini_parse(t_cub *cub);
int				is_player(char c);

/* ---- Map Parsing ---- */
char			**freemap(char **map, char **str);
int				check_extention(char *path, char const *cub);

/* ---- Map Parsing & Validation ---- */
void			line_iterating(t_cub *cub);
void			parse_map(t_cub *cub, int line_num);
void			extend_map(t_cub *cub, int line_num);
void			read_file(t_cub *cub, char *file);
char			*extend_str(char *s1, char *s2);
int				check_type(char c);
void			store_player_location(t_cub *cub, int row, int col);
void			check_map_content(t_cub *cub, int line_num);
void			validate_current_location(t_cub *cub, int row, int col,
					char **map);
void			validate_borders(t_cub *cub, char **map);
void			parsing(t_cub *cub);
void			execution(t_cub *cub);
void			init_player_vectors(t_cub *cub);
void			set_value(t_vec *target, double x, double y);
void			load_images(t_cub *cub);
int				get_color(int rgb[3]);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			render_background(t_cub *cub);
void			raycast(t_cub *cub);
void			clean_mlx(t_cub *cub);

/* ---- Movement ---- */
int				handle_keypress(int keysym, t_cub *cub);
void			move_player(t_cub *cub, double dx, double dy);
void			rotate_direction(t_cub *cub, double angle);
int				game_loop(t_cub *cub);

/* ---- Utils ---- */
void			two_step_free(void **var);
void			free_2d_array(char ***arr);
char			**cpymap(char **map);
t_point			xy_p(char **map);
int				ft_strcmp(const char *s1, const char *s2);
int				arr_len(char **arr);

#endif