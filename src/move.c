
#include "headers/header.h"

void	rotate_direction(t_cub *cub, double new_x, double new_y)
{
	if 
}

int	handle_keypress(int keysym, t_cub *cub)
{
	if (keysym == KEY_ESC)
		handle_exit(cub, NULL, 0);
	else if (keysym == KEY_UP || keysym == 'w')
		move_player();
	else if (keysym == KEY_DOWN || keysym == 's')
		move_player();
	else if (keysym == KEY_LEFT || keysym == 'a')
		set_value(&cub->exec.dir, cub->exec.dir.x, 0.0);
	else if (keysym == KEY_RIGHT || keysym == 'd')
		move_player();
	return (0);
}
