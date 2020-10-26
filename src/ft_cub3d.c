/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:48:38 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/26 10:29:54 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_cub3d.h"

void	player_init(t_mlx *mlx)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	player->pos.x = 0;
	player->pos.y = 0;
	player->dir.x = -1;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0.86;
	mlx->zbuffer = NULL;
	mlx->player = player;
}

void	player_orientation(t_mlx *mlx, int x, int y)
{
	if (mlx->player->spawn.x == -1)
	{
		mlx->player->spawn.x = x;
		mlx->player->spawn.y = y;
	}
	else
		error_manager(4, mlx);
	mlx->player->pos.x = (double)x + 0.5;
	mlx->player->pos.y = (double)y + 0.5;
	if (mlx->map[x][y] == 'E')
		rot_right(mlx, 1.6);
	if (mlx->map[x][y] == 'S')
		rot_right(mlx, 3.1);
	if (mlx->map[x][y] == 'W')
		rot_right(mlx, 4.7);
	if (mlx->map[x][y] == 'N')
		rot_right(mlx, 6.3);
	mlx->map[x][y] = '0';
}

void	check_player_pos(t_mlx *mlx)
{
	int x;
	int y;

	x = 0;
	y = 0;
	mlx->player->spawn.x = -1;
	mlx->player->spawn.y = -1;
	while (x < mlx->map_height)
	{
		while (y < mlx->map_width)
		{
			if (mlx->map[x][y] == 'N' || mlx->map[x][y] == 'S'
			|| mlx->map[x][y] == 'E' || mlx->map[x][y] == 'W')
				player_orientation(mlx, x, y);
			y++;
		}
		y = 0;
		x++;
	}
	if (mlx->player->spawn.x == -1 || mlx->player->spawn.y == -1)
		error_manager(4, mlx);
}

void	engine(t_mlx *mlx, char *argv[])
{
	check_name(mlx, argv[1]);
	parsing(argv[1], mlx);
	check_player_pos(mlx);
	map_check(mlx);
	parsing_sprite(mlx, mlx->sprite);
	mlx->window = mlx_new_window(mlx->mlx,
	mlx->screen_width, mlx->screen_height, "ft_cub3d");
	put_frame(mlx);
	floor_ceiling(mlx);
	raycasting(mlx);
	mlx_hook(mlx->window, 2, 0, key_check, mlx);
	mlx_hook(mlx->window, 17L, 0, (int (*)())(serpilliere), mlx);
	mlx_loop(mlx->mlx);
	serpilliere(mlx);
}

int		main(int argc, char *argv[])
{
	t_mlx	*mlx;

	if (!(mlx = malloc(sizeof(t_mlx))))
		error_manager(3, mlx);
	mlx->capture = 0;
	mlx->mlx = mlx_init();
	if (argc == 3 && ft_strncmp(argv[2], "--save\0", 7) == 0)
		mlx->capture = 1;
	else if ((argc == 3 && mlx->capture != 1)
	|| (argc != 2 && mlx->capture == 0))
		error_manager(6, mlx);
	if (!(mlx->sprite = malloc(sizeof(t_sprite))))
		error_manager(3, mlx);
	if (!(mlx->ray = malloc(sizeof(t_ray))))
		error_manager(3, mlx);
	if (!(mlx->fnc = malloc(sizeof(t_fnc))))
		error_manager(3, mlx);
	mlx->frame = NULL;
	if (mlx->mlx == 0)
		return (1);
	player_init(mlx);
	engine(mlx, argv);
	return (0);
}
