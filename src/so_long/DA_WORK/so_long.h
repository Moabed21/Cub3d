/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:11:28 by melshata          #+#    #+#             */
/*   Updated: 2026/07/18 15:22:08 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include "libft.h"
# include "printf.h"
# include "mlx.h"

# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define IMG_SIZE 64

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

char	**freemap(char **map, char **str);
int		check_extention(char *path, char const *ber);
int		phasing(char **text);
char	**read_and_check_nums(char *path);
int		map_walls_check(char **map);
int		map_check_rect(char **map);
int		reach(char **map, t_point xy, char to_count, int firstcall);
char	**cpymap(char **map);
t_point	xy_p(char **map);
int		collect_num(char **map);
char	**map_manager(char *path);

int		handle_exit(t_game *game, int exit_code, const char *msg);
void	set_xy(t_game *game, char **map);
void	load_photos(t_game *game);
int		render_frame(t_game *game);
void	initiate_game(t_game *game);
int		handle_keypress(int keysym, t_game *game);

#endif
