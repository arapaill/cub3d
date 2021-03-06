/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:34:54 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/26 10:29:53 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_cub3d.h"

static void	left_key(t_mlx *mlx)
{
	if (mlx->map[(int)(mlx->player->pos.x - mlx->player->dir.y * MOVESPEED)]
	[(int)mlx->player->pos.y] == '0')
		mlx->player->pos.x -= mlx->player->dir.y * MOVESPEED;
	if (mlx->map[(int)(mlx->player->pos.x)]
	[(int)(mlx->player->pos.y + mlx->player->dir.x * MOVESPEED)] == '0')
		mlx->player->pos.y += mlx->player->dir.x * MOVESPEED;
}

static void	up_key(t_mlx *mlx)
{
	if (mlx->map[(int)(mlx->player->pos.x + mlx->player->dir.x * MOVESPEED)]
	[(int)mlx->player->pos.y] == '0')
		mlx->player->pos.x += mlx->player->dir.x * MOVESPEED;
	if (mlx->map[(int)(mlx->player->pos.x)]
	[(int)(mlx->player->pos.y + mlx->player->dir.y * MOVESPEED)] == '0')
		mlx->player->pos.y += mlx->player->dir.y * MOVESPEED;
}

static void	down_key(t_mlx *mlx)
{
	if (mlx->map[(int)(mlx->player->pos.x - mlx->player->dir.x * MOVESPEED)]
	[(int)(mlx->player->pos.y)] == '0')
		mlx->player->pos.x -= mlx->player->dir.x * MOVESPEED;
	if (mlx->map[(int)(mlx->player->pos.x)]
	[(int)(mlx->player->pos.y - mlx->player->dir.y * MOVESPEED)] == '0')
		mlx->player->pos.y -= mlx->player->dir.y * MOVESPEED;
}

static void	right_key(t_mlx *mlx)
{
	if (mlx->map[(int)(mlx->player->pos.x + mlx->player->dir.y * MOVESPEED)]
	[(int)mlx->player->pos.y] == '0')
		mlx->player->pos.x += mlx->player->dir.y * MOVESPEED;
	if (mlx->map[(int)(mlx->player->pos.x)]
	[(int)(mlx->player->pos.y - mlx->player->dir.x * MOVESPEED)] == '0')
		mlx->player->pos.y -= mlx->player->dir.x * MOVESPEED;
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
		rot_right(mlx, 0.08);
	if (key == LEFT_KEY)
		rot_left(mlx, 0.08);
	if (key == ESC_KEY)
		serpilliere(mlx);
	mlx_clear_window(mlx->mlx, mlx->window);
	floor_ceiling(mlx);
	raycasting(mlx);
	return (1);
}
