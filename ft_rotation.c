/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 08:45:40 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/20 08:46:21 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	rot_left(t_mlx *mlx, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = mlx->player->dir.x;
	old_plane_x = mlx->player->plane.x;
	mlx->player->dir.x = mlx->player->dir.x *
	cos(rot_speed) - mlx->player->dir.y * sin(rot_speed);
	mlx->player->dir.y = old_dir_x *
	sin(rot_speed) + mlx->player->dir.y * cos(rot_speed);
	mlx->player->plane.x = mlx->player->plane.x *
	cos(rot_speed) - mlx->player->plane.y * sin(rot_speed);
	mlx->player->plane.y = old_plane_x *
	sin(rot_speed) + mlx->player->plane.y * cos(rot_speed);
}

void	rot_right(t_mlx *mlx, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = mlx->player->dir.x;
	old_plane_x = mlx->player->plane.x;
	mlx->player->dir.x = mlx->player->dir.x *
	cos(-rot_speed) - mlx->player->dir.y * sin(-rot_speed);
	mlx->player->dir.y = old_dir_x *
	sin(-rot_speed) + mlx->player->dir.y * cos(-rot_speed);
	mlx->player->plane.x = mlx->player->plane.x *
	cos(-rot_speed) - mlx->player->plane.y * sin(-rot_speed);
	mlx->player->plane.y = old_plane_x *
	sin(-rot_speed) + mlx->player->plane.y * cos(-rot_speed);
}
