/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_nxt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:49:52 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/29 12:51:04 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_cub3d.h"

void	put_frame(t_mlx *mlx)
{
	if (mlx->frame != NULL)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->frame, 0, 0);
		mlx_destroy_image(mlx->mlx, mlx->frame);
	}
	mlx->frame = mlx_new_image(mlx->mlx, mlx->screen_width, mlx->screen_height);
	mlx->data =
		(int*)mlx_get_data_addr(mlx->frame, &mlx->bpp, &mlx->sl, &mlx->endian);
}

void	pre_hit(t_mlx *mlx, t_ray *ray)
{
	if (ray->raydir.x < 0)
	{
		ray->d_step.x = -1;
		ray->sidedist.x =
		(mlx->player->pos.x - ray->map.x) * ray->deltadist.x;
	}
	else
	{
		ray->d_step.x = 1;
		ray->sidedist.x =
		(ray->map.x + 1.0 - mlx->player->pos.x) * ray->deltadist.x;
	}
	if (ray->raydir.y < 0)
	{
		ray->d_step.y = -1;
		ray->sidedist.y =
		(mlx->player->pos.y - ray->map.y) * ray->deltadist.y;
	}
	else
	{
		ray->d_step.y = 1;
		ray->sidedist.y =
		(ray->map.y + 1.0 - mlx->player->pos.y) * ray->deltadist.y;
	}
}

void	hit(t_mlx *mlx, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->map.x += ray->d_step.x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->d_step.y;
			ray->side = 1;
		}
		if (mlx->map[(int)ray->map.x][(int)ray->map.y] > '0')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perpwalldist =
			(ray->map.x - mlx->player->pos.x +
			(1 - ray->d_step.x) / 2) / ray->raydir.x;
	else
		ray->perpwalldist =
			(ray->map.y - mlx->player->pos.y +
			(1 - ray->d_step.y) / 2) / ray->raydir.y;
}
