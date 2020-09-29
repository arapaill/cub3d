/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:34:54 by arapaill          #+#    #+#             */
/*   Updated: 2020/09/29 16:43:42 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static void	rot_left(t_mlx *mlx)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = mlx->player->dirX;
	old_plane_x = mlx->player->planeX;
	mlx->player->dirX = mlx->player->dirX *
	cos(rotspeed) - mlx->player->dirY * sin(rotspeed);
	mlx->player->dirY = old_dir_x *
	sin(rotspeed) + mlx->player->dirY * cos(rotspeed);
	mlx->player->planeX = mlx->player->planeX *
	cos(rotspeed) - mlx->player->planeY * sin(rotspeed);
	mlx->player->planeY = old_plane_x *
	sin(rotspeed) + mlx->player->planeY * cos(rotspeed);
}

static void	rot_right(t_mlx *mlx)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = mlx->player->dirX;
	old_plane_x = mlx->player->planeX;
	mlx->player->dirX = mlx->player->dirX *
	cos(-rotspeed) - mlx->player->dirY * sin(-rotspeed);
	mlx->player->dirY = old_dir_x *
	sin(-rotspeed) + mlx->player->dirY * cos(-rotspeed);
	mlx->player->planeX = mlx->player->planeX *
	 cos(-rotspeed) - mlx->player->planeY * sin(-rotspeed);
	mlx->player->planeY = old_plane_x *
	sin(-rotspeed) + mlx->player->planeY * cos(-rotspeed);
}

static void	left_key(t_mlx *mlx)
{
	if (mlx->map[(int)(mlx->player->posX - mlx->player->dirY * movespeed)]
	[(int)mlx->player->posY] == '0')
		mlx->player->posX -= mlx->player->dirY * movespeed;
	if (mlx->map[(int)(mlx->player->posX)]
	[(int)(mlx->player->posY + mlx->player->dirX * movespeed)] == '0')
		mlx->player->posY += mlx->player->dirX * movespeed;
}

static void	up_key(t_mlx *mlx)
{
	if (mlx->map[(int)(mlx->player->posX + mlx->player->dirX * movespeed)]
	[(int)mlx->player->posY] == '0')
		mlx->player->posX += mlx->player->dirX * movespeed;
	if (mlx->map[(int)(mlx->player->posX)]
	[(int)(mlx->player->posY + mlx->player->dirY * movespeed)] == '0')
		mlx->player->posY += mlx->player->dirY * movespeed;
}

static void	down_key(t_mlx *mlx)
{
	if (mlx->map[(int)(mlx->player->posX - mlx->player->dirX * movespeed)]
	[(int)(mlx->player->posY)] == '0')
		mlx->player->posX -= mlx->player->dirX * movespeed;
	if (mlx->map[(int)(mlx->player->posX)]
	[(int)(mlx->player->posY - mlx->player->dirY * movespeed)] == '0')
		mlx->player->posY -= mlx->player->dirY * movespeed;
}

static void	right_key(t_mlx *mlx)
{
	if (mlx->map[(int)(mlx->player->posX + mlx->player->dirY * movespeed)]
	[(int)mlx->player->posY] == '0')
		mlx->player->posX += mlx->player->dirY * movespeed;
	if (mlx->map[(int)(mlx->player->posX)]
	[(int)(mlx->player->posY - mlx->player->dirX * movespeed)] == '0')
		mlx->player->posY -= mlx->player->dirX * movespeed;
}

int			key_check(int key, t_mlx *mlx)
{
	if (key == A_KEY)
		left_key(mlx);
	if (key == W_KEY)
		up_key(mlx);
	if (key == S_KEY)
		down_key(mlx);
	if (key == D_KEY)
		right_key(mlx);
	if (key == RIGHT_KEY)
		rot_right(mlx);
	if (key == LEFT_KEY)
		rot_left(mlx);
	if (key == ESC_KEY)
		exit(0);
	mlx_clear_window(mlx->mlx, mlx->window);
	floor_ceiling(mlx);
	raycasting(mlx);
	return (1);
}
