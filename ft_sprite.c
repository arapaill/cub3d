/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:23:53 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/09 11:09:23 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	ordersprites(t_sort *sprite, int amount, double *dist)
{
	t_sort		buff;
	double		buffdist;
	int			i;

	i = 0;
	while (i < amount - 1)
	{
		if (dist[i] < dist[i + 1])
		{
			ft_memcpy(&buff, &sprite[i], sizeof(t_sort));
			ft_memcpy(&sprite[i], &sprite[i + 1], sizeof(t_sort));
			ft_memcpy(&sprite[i + 1], &buff, sizeof(t_sort));
			buffdist = dist[i];
			dist[i] = dist[i + 1];
			dist[i + 1] = buffdist;
			i = -1;
		}
		i++;
	}
}

void	sortsprite(int *order, double *dist, int amount, t_mlx *mlx)
{
	t_sort		*sprite;
	int			i;

	if (!(sprite = malloc(sizeof(t_sort) * amount)))
		error_manager(3, mlx);
	i = -1;
	while (++i < amount)
	{
		sprite[i].first = dist[i];
		sprite[i].second = order[i];
	}
	i = -1;
	ordersprites(sprite, amount, dist);
	while (++i < amount)
	{
		dist[i] = sprite[i].first;
		order[i] = sprite[i].second;
	}
	free(sprite);
}

void	drawsprite(t_mlx *mlx, t_sprite *sprite)
{
	int			i;
	int			y;
	int			d;
	i = -1;
	while (++i < mlx->spritenbr)
	{
		sprite->spriteX =
		sprite->p_sprite[sprite->spriteorder[i]].x - mlx->player->posX;
		sprite->spriteY =
		sprite->p_sprite[sprite->spriteorder[i]].y - mlx->player->posY;
		sprite->invdet =
		1.0 / (mlx->player->planeX * mlx->player->dirY
		- mlx->player->dirX * mlx->player->planeY);
		sprite->transformX =
		sprite->invdet * (mlx->player->dirY *
		sprite->spriteX - mlx->player->dirX * sprite->spriteY);
		sprite->transformY =
		sprite->invdet * (-(mlx->player->planeY)
		* sprite->spriteX + mlx->player->planeX * sprite->spriteY);
		sprite->spriteScreenX = (mlx->screen_width / 2)
		* (1 + sprite->transformX / sprite->transformY);
		sprite->spriteHeight =
		abs((int)(mlx->screen_height / (sprite->transformY)));
		sprite->drawStart.y =
		-(sprite->spriteHeight) / 2 + mlx->screen_height / 2;
		if (sprite->drawStart.y < 0)
			sprite->drawStart.y = 0;
		sprite->drawEnd.y = sprite->spriteHeight / 2 + mlx->screen_height / 2;
		if (sprite->drawEnd.y >= mlx->screen_height)
			sprite->drawEnd.y = mlx->screen_height - 1;
		sprite->spriteWidth =
		abs((int)(mlx->screen_height / (sprite->transformY)));
		sprite->drawStart.x =
		-(sprite->spriteWidth) / 2 + sprite->spriteScreenX;
		if (sprite->drawStart.x < 0)
			sprite->drawStart.x = 0;
		sprite->drawEnd.x = sprite->spriteWidth / 2 + sprite->spriteScreenX;
		if (sprite->drawEnd.x >= mlx->screen_width)
			sprite->drawEnd.x = mlx->screen_width - 1;
		sprite->stripe = sprite->drawStart.x;
		while (sprite->stripe < sprite->drawEnd.x)
		{
			sprite->tex.x = (int)(256 * (sprite->stripe
			- (-(sprite->spriteWidth) / 2 + sprite->spriteScreenX))
			* texWidth / sprite->spriteWidth) / 256;
			if (sprite->transformY > 0 && sprite->stripe > 0 &&
			sprite->stripe < mlx->screen_width &&
			sprite->transformY < mlx->zbuffer[sprite->stripe])
			{
				y = sprite->drawStart.y;
				while (y < sprite->drawEnd.y)
				{
					d = (y) * 256 - mlx->screen_height *
					128 + sprite->spriteHeight * 128;
					sprite->tex.y = ((d * texHeight) /
					sprite->spriteHeight) / 256;
					sprite->color = mlx->texture->sprite
					[(texHeight * sprite->tex.y) + sprite->tex.x];
					if ((sprite->color & 0x00FFFFFF) != 0)
						mlx->data[sprite->stripe +
						(y * mlx->screen_width)] = sprite->color;
					y++;
				}
			}
			sprite->stripe++;
		}
	}
}

void	add_sprites(t_mlx *mlx)
{
	int			i;
	t_sprite	*sprite;
	sprite = mlx->sprite;
	i = -1;
	while (++i < mlx->spritenbr)
	{
		sprite->spriteorder[i] = i;
		sprite->spritedist[i] =
		sqrt(pow(mlx->player->posX - sprite->p_sprite[i].x, 2) +
		pow(mlx->player->posY - sprite->p_sprite[i].y, 2));
	}
	sortsprite(sprite->spriteorder, sprite->spritedist, mlx->spritenbr, mlx);
	drawsprite(mlx, sprite);
}
