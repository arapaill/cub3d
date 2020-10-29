/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 13:34:29 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/29 12:13:03 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_cub3d.h"

void	pre_ray(t_mlx *mlx, t_ray *ray)
{
	ray->camerax = 2 * ray->x / (double)ray->w - 1;
	ray->raydir.x = mlx->player->dir.x
	+ mlx->player->plane.x * ray->camerax;
	ray->raydir.y = mlx->player->dir.y +
	mlx->player->plane.y * ray->camerax;
	ray->map.x = (int)mlx->player->pos.x;
	ray->map.y = (int)mlx->player->pos.y;
	if (ray->raydir.y == 0)
		ray->deltadist.x = 0;
	else if (ray->raydir.x == 0)
		ray->deltadist.x = 1;
	else
		ray->deltadist.x = fabs(1 / ray->raydir.x);
	if (ray->raydir.x == 0)
		ray->deltadist.y = 0;
	else if (ray->raydir.y == 0)
		ray->deltadist.x = 1;
	else
		ray->deltadist.y = fabs(1 / ray->raydir.y);
	ray->hit = 0;
}

void	pre_cast(t_mlx *mlx, t_ray *ray)
{
	ray->lineheight = (int)(ray->h / ray->perpwalldist);
	ray->drawstart = -ray->lineheight / 2 + ray->h / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + ray->h / 2;
	if (ray->drawend >= ray->h)
		ray->drawend = ray->h - 1;
	if (ray->side == 0)
		ray->wallx = mlx->player->pos.y + ray->perpwalldist * ray->raydir.y;
	else
		ray->wallx = mlx->player->pos.x + ray->perpwalldist * ray->raydir.x;
	ray->wallx -= floor((ray->wallx));
	ray->tex.x = (int)(ray->wallx * (double)TEXWIDTH);
	if (ray->side == 0 && ray->raydir.x > 0)
		ray->tex.x = TEXWIDTH - ray->tex.x - 1;
	if (ray->side == 1 && ray->raydir.y < 0)
		ray->tex.x = TEXWIDTH - ray->tex.x - 1;
	ray->step = 1.0 * TEXHEIGHT / ray->lineheight;
	ray->texpos = (ray->drawstart -
	ray->h / 2 + ray->lineheight / 2) * ray->step;
	ray->y = ray->drawstart - 1;
}

void	cast(t_mlx *mlx, t_ray *ray)
{
	while (++ray->y < ray->drawend)
	{
		ray->tex.y = (int)ray->texpos & (TEXHEIGHT - 1);
		ray->texpos += ray->step;
		if (ray->side == 1)
		{
			if (ray->raydir.y >= 0)
				mlx->color = mlx->texture->west
				[(TEXHEIGHT * ray->tex.y) + ray->tex.x];
			else
				mlx->color = mlx->texture->east
				[(TEXHEIGHT * ray->tex.y) + ray->tex.x];
		}
		else
		{
			if (ray->raydir.x >= 0)
				mlx->color = mlx->texture->north
				[(TEXHEIGHT * ray->tex.y) + ray->tex.x];
			else
				mlx->color = mlx->texture->south
				[(TEXHEIGHT * ray->tex.y) + ray->tex.x];
		}
		mlx->data[ray->x - 1 + ray->y * mlx->screen_width] = mlx->color;
	}
}

void	roll(t_mlx *mlx, t_ray *ray)
{
	while (++ray->x < ray->w)
	{
		pre_ray(mlx, ray);
		pre_hit(mlx, ray);
		hit(mlx, ray);
		pre_cast(mlx, ray);
		cast(mlx, ray);
		mlx->zbuffer[ray->x] = ray->perpwalldist;
	}
}

int		raycasting(t_mlx *mlx)
{
	t_ray	*ray;

	ray = mlx->ray;
	ray->x = 0;
	ray->y = 0;
	ray->hit = 0;
	ray->w = mlx->screen_width;
	ray->h = mlx->screen_height;
	free(mlx->zbuffer);
	if (!(mlx->zbuffer = malloc(sizeof(double *) * mlx->screen_width)))
		error_manager(3, mlx);
	roll(mlx, ray);
	add_sprites(mlx);
	if (mlx->capture == 1)
		bmp_capture(mlx);
	put_frame(mlx);
	return (0);
}
