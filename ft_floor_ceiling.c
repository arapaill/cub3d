/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor_ceiling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:57:50 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/19 16:32:20 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	rgba_floor_ceiling(t_mlx *mlx)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < mlx->screen_width)
	{
		while (y < mlx->screen_height / 2)
		{
			mlx->data[x + (y++ * mlx->screen_width)] = mlx->texture->rgb_floor;
			//printf(" y = %d\n", y);
		}
		x++;
		y = 0;
	}
	//printf(" x = %d\n", x);
	x = 0;
	y = mlx->screen_height / 2;
	while (x < mlx->screen_width)
	{
		while (y < mlx->screen_height)
			mlx->data[x + (y++ * mlx->screen_width)] = mlx->texture->rgb_ceiling;
		x++;
		y = mlx->screen_height / 2;
	}
}

void	floor_ceiling(t_mlx *mlx)
{
	t_fnc	*fnc
	int		p;
	int		y;
	int		x;
	int		h;

	fnc = mlx->fnc;
	y = 0;
	h = mlx->screen_height;
	if (mlx->texture->rgb_floor == 0 && mlx->texture->rgb_ceiling == 0)
	{
		while (++y < h)
		{
			rayDirX0 = mlx->player->dir.x - mlx->player->plane.x;
			rayDirY0 = mlx->player->dir.y - mlx->player->plane.y;
			rayDirX1 = mlx->player->dir.x + mlx->player->plane.x;
			rayDirY1 = mlx->player->dir.y + mlx->player->plane.y;
			p = y - mlx->screen_height / 2;
			posZ = 0.5 * mlx->screen_height;
			rowDistance = posZ / p;
			floorStepX = rowDistance * (rayDirX1 - rayDirX0) / mlx->screen_width;
			floorStepY = rowDistance * (rayDirY1 - rayDirY0) / mlx->screen_width;
			floorX = mlx->player->pos.x + rowDistance * rayDirX0;
			floorY = mlx->player->pos.y + rowDistance * rayDirY0;
			x = 0;
			while (++x < (int)(mlx->screen_width))
			{
				cellX = (int)(floorX);
				cellY = (int)(floorY);
				tx = (int)(TEXWIDTH * (floorX - cellX)) & (TEXWIDTH - 1);
				ty = (int)(TEXHEIGHT * (floorY - cellY)) & (TEXHEIGHT - 1);
				floorX += floorStepX;
				floorY += floorStepY;
				color = mlx->texture->floor[TEXWIDTH * ty + tx];
				color = (color >> 1) & 8355711;
				mlx->data[x + (y * mlx->screen_width)] = color;        
				color = mlx->texture->ceiling[TEXWIDTH * ty + tx];
				color = (color >> 1) & 8355711;
				mlx->data[x + ((mlx->screen_height - y - 1) * mlx->screen_width)] = color;
			}
		}
	}
	else
		rgba_floor_ceiling(mlx);
}
