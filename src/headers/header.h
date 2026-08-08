/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:20:51 by moabed            #+#    #+#             */
/*   Updated: 2026/08/08 21:51:47 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

/* ---- Key Codes ---- */
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

/* ---- Image / Buffer ---- */
# define IMG_SIZE 64

/* ---- Structs ---- */

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map_base;
	char		**map_grid;
	void		*wall_img;
	void		*floor_img;
	void		*player_img;
	void		*collect_img;
	void		*exit_img;
	int			player_x;
	int			player_y;
	int			map_x;
	int			map_y;
	int			collected;
}				t_game;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_cub
{
	t_point		player_start_point;  // starting point as (x, y)
	char		direction;  // N, E, S, W
	char		*n_side;  // path of image of north side of a wall
	char		*s_side;
	char		*e_side;
	char		*w_side;
	char 		*ceiling;
	char 		*floor;
	char		*lines; // one for whole file
	char 		**temp_sep_line;
	char		**splitted_lines;	//	one for map 
	int 		data_count;
}				t_cub;

/* ---- Error Handling & Cub Init ---- */
void	initiate_cub(t_cub *cub);
void	free_cub(t_cub *cub);
void	raise_exception(t_cub *cub, char *message);

/* ---- Map Parsing ---- */
char	**freemap(char **map, char **str);
int		check_extention(char *path, char const *cub);

/* ---- Map Validation ---- */
int		phasing(char **text);
int		map_walls_check(char **map);
int		map_check_rect(char **map);
int		reach(char **map, t_point xy, char to_count, int firstcall);
char	**cpymap(char **map);
t_point	xy_p(char **map);
int		ft_strcmp(const char *s1, const char *s2);
void	line_iterating(t_cub *cub);

/* ---- Game Init / Exit ---- */
void	initiate_game(char *file,t_game *game, t_cub *cub);
void	handle_exit(t_game *game, t_cub *cub, int exit_code, const char *msg);

/* ---- Render (TODO: bring sources in) ---- */
void	set_xy(t_game *game, char **map);
void	load_photos(t_game *game);
int		render_frame(t_game *game);
int		handle_keypress(int keysym, void *param);
int		close_window(void *param);

#endif