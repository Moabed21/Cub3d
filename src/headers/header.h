/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:20:51 by moabed            #+#    #+#             */
/*   Updated: 2026/08/09 21:50:17 by moabed           ###   ########.fr       */
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

/* ---- Structs ---- */

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_ray
{
	int		f_rgb[3];
	int 	c_rgb[3]; // cuz these will be used in execution phase
	t_point	player_start_point;

}			t_ray;

typedef struct s_cub
{
	// starting point as (x, y)
	t_ray	exec;
	char 	direction; // N, E, S, W
	char 	*n_side;   // path of image of north side of a wall
	char	*s_side;
	char	*e_side;
	char	*w_side;
	char	*ceiling;
	char	*floor;
	char 	*lines; // one for whole file
	char	**temp_sep_line;
	char 	**splitted_lines; // one for map
	int		data_count;
}			t_cub;

/* ---- Error Handling & Cub Init ---- */
void		initiate_cub(t_cub *cub);
void		free_cub(t_cub *cub);
void		raise_exception(t_cub *cub, char *message);
void		mini_parse(t_cub *cub);

/* ---- Map Parsing ---- */
char		**freemap(char **map, char **str);
int			check_extention(char *path, char const *cub);

/* ---- Map Parsing & Validation ---- */
void		line_iterating(t_cub *cub);
void		extend_map(t_cub *cub, int line_num);
void		read_file(t_cub *cub, char *file);

/* ---- Utils ---- */
void		two_step_free(void **var);
void		free_2d_array(char ***arr);
char		**cpymap(char **map);
t_point		xy_p(char **map);
int			ft_strcmp(const char *s1, const char *s2);
int			arr_len(char **arr);

#endif