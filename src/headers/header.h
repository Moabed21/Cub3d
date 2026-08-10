/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:20:51 by moabed            #+#    #+#             */
/*   Updated: 2026/08/10 13:19:04 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../libft/libft.h"
# include "../../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* ---- Key Codes ---- */
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define WIDTH 1920
# define HEIGHT 1080

/* ---- Error Codes ---- */
typedef enum e_err_code
{
	ERR_NONE = 0,
	ERR_ARG_COUNT,
	ERR_FILE_EXT,
	ERR_FILE_OPEN,
	ERR_MALLOC,
	ERR_DUPLICATE_ELEMENT,
	ERR_MISSING_REQUIREMENTS,
	ERR_COLOR_RANGE,
	ERR_MAP_CONTENT,
	ERR_PLAYER_COUNT,
	ERR_MAP_OPEN,
	ERR_MLX_INIT,
	ERR_MLX_WIN
}	t_err_code;

/* ---- Structs ---- */

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_mlx
{
	void		*connection;
	void		*window;
	t_img		*img;
}		t_mlx;

typedef struct s_ray
{
	int		f_rgb[3];
	int 	c_rgb[3]; // cuz these will be used in execution phase
	t_point	player_start_point;
	char 	direction; // N, E, S, W

}			t_ray;

typedef struct s_cub
{
	t_ray		exec;
	t_mlx 		mlx_ops;
	t_err_code	err_code;
	char 		*n_side;   // path of image of north side of a wall
	char		*s_side;
	char		*e_side;
	char		*w_side;
	char		*ceiling;
	char		*floor;
	char 		*lines; // one for whole file
	char		**temp_sep_line;
	char		**map;
	char 		**splitted_lines; // one for map
	int			data_count;
}			t_cub;

/* ---- Error Handling & Cub Init ---- */
void		initiate_cub(t_cub *cub);
void		free_cub(t_cub *cub);
void		raise_exception(t_cub *cub, t_err_code code);
char		*get_parsing_err_msg(t_err_code code);
char		*get_exec_err_msg(t_err_code code);
char		*get_error_msg(t_err_code code);
void		mini_parse(t_cub *cub);
int			is_player(char c);
 
/* ---- Map Parsing ---- */
char		**freemap(char **map, char **str);
int			check_extention(char *path, char const *cub);

/* ---- Map Parsing & Validation ---- */
void		line_iterating(t_cub *cub);
void		parse_map(t_cub *cub, int line_num);
void		extend_map(t_cub *cub, int line_num);
void		read_file(t_cub *cub, char *file);
char		*extend_str(char *s1, char *s2);
int			check_type(char c);
void		store_player_location(t_cub *cub, int row, int col);
void		check_map_content(t_cub *cub, int line_num);
void		validate_current_location(t_cub *cub, int row, int col, char **map);
void		validate_borders(t_cub *cub, char **map);
void		parsing(t_cub *cub);
void	    execution(t_cub *cub);

/* ---- Utils ---- */
void		two_step_free(void **var);
void		free_2d_array(char ***arr);
char		**cpymap(char **map);
t_point		xy_p(char **map);
int			ft_strcmp(const char *s1, const char *s2);
int			arr_len(char **arr);

#endif