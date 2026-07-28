/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:20:51 by moabed            #+#    #+#             */
/*   Updated: 2026/07/18 15:21:51 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

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
	char		**map;
}				t_cub;

/* ---- GNL Utils ---- */
ssize_t	ll(char *s);
void	*fullfree(char **s1, char **s2, char **s3);
char	*schr(char *s, char c);
char	*my_strjoin(char *s1, char *s2);

/* ---- GNL ---- */
char	*get_next_line(int fd);

/* ---- Map Parsing ---- */
char	**freemap(char **map, char **str);
int		check_extention(char *path, char const *cub);
char	**read_and_check_nums(char *path);
char	**map_manager(char *path);

/* ---- Map Validation ---- */
int		phasing(char **text);
int		map_walls_check(char **map);
int		map_check_rect(char **map);
int		reach(char **map, t_point xy, char to_count, int firstcall);
char	**cpymap(char **map);
t_point	xy_p(char **map);

/* ---- Game Init / Exit ---- */
void	initiate_game(t_game *game, t_cub *cub);
int		handle_exit(t_game *game, int exit_code, const char *msg);

/* ---- Render (TODO: bring sources in) ---- */
void	set_xy(t_game *game, char **map);
void	load_photos(t_game *game);
int		render_frame(t_game *game);
int		handle_keypress(int keysym, void *param);
int		close_window(void *param);

/* ---- Libft Utilities ---- */
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);

#endif