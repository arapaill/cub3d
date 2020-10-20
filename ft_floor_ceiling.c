/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor_ceiling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:57:50 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/20 08:39:24 by arapaill         ###   ########.fr       */
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
			mlx->data[x + (y++ * mlx->screen_width)] = mlx->texture->rgb_floor;
		x++;
		y = 0;
	}
	x = 0;
	y = mlx->screen_height / 2;
	while (x < mlx->screen_width)
	{
		while (y < mlx->screen_height)
			mlx->data[x +
			(y++ * mlx->screen_width)] = mlx->texture->rgb_ceiling;
		x++;
		y = mlx->screen_height / 2;
	}
}

void	rollfnc(t_mlx *mlx, t_fnc *fnc, int y)
{
	int		x;

	x = 0;
	while (++x < (int)(mlx->screen_width))
	{
		fnc->cell.x = (int)(fnc->floor.x);
		fnc->cell.y = (int)(fnc->floor.y);
		fnc->t.x = (int)(TEXWIDTH *
		(fnc->floor.x - fnc->cell.x)) & (TEXWIDTH - 1);
		fnc->t.y = (int)(TEXHEIGHT *
		(fnc->floor.y - fnc->cell.y)) & (TEXHEIGHT - 1);
		fnc->floor.x += fnc->floorstep.x;
		fnc->floor.y += fnc->floorstep.y;
		fnc->color = mlx->texture->floor
		[TEXWIDTH * fnc->t.y + fnc->t.x];
		fnc->color = (fnc->color >> 1) & 8355711;
		mlx->data[x + (y * mlx->screen_width)] = fnc->color;
		fnc->color = mlx->texture->ceiling
		[TEXWIDTH * fnc->t.y + fnc->t.x];
		fnc->color = (fnc->color >> 1) & 8355711;
		mlx->data[x + ((mlx->screen_height - y - 1) *
		mlx->screen_width)] = fnc->color;
	}
}

void	prepfnc(t_mlx *mlx, t_fnc *fnc, int y)
{
	int		p;

	fnc->raydira.x = mlx->player->dir.x - mlx->player->plane.x;
	fnc->raydira.y = mlx->player->dir.y - mlx->player->plane.y;
	fnc->raydirb.x = mlx->player->dir.x + mlx->player->plane.x;
	fnc->raydirb.y = mlx->player->dir.y + mlx->player->plane.y;
	p = y - mlx->screen_height / 2;
	fnc->posz = 0.5 * mlx->screen_height;
	fnc->rowdistance = fnc->posz / p;
	fnc->floorstep.x = fnc->rowdistance *
	(fnc->raydirb.x - fnc->raydira.x) / mlx->screen_width;
	fnc->floorstep.y = fnc->rowdistance *
	(fnc->raydirb.y - fnc->raydira.y) / mlx->screen_width;
	fnc->floor.x = mlx->player->pos.x +
	fnc->rowdistance * fnc->raydira.x;
	fnc->floor.y = mlx->player->pos.y +
	fnc->rowdistance * fnc->raydira.y;
}

void	floor_ceiling(t_mlx *mlx)
{
	t_fnc	*fnc;
	int		y;
	int		h;

	fnc = mlx->fnc;
	y = 0;
	h = mlx->screen_height;
	if (mlx->texture->rgb_floor == 0 && mlx->texture->rgb_ceiling == 0)
	{
		while (++y < h)
		{
			prepfnc(mlx, fnc, y);
			rollfnc(mlx, fnc, y);
		}
	}
	else
		rgba_floor_ceiling(mlx);
}
