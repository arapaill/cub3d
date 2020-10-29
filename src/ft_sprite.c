/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:23:53 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/29 12:29:15 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_cub3d.h"

void	pre_draw(t_mlx *mlx, t_sprite *sprite, int i)
{
	sprite->d_sprite.x =
	sprite->p_sprite[sprite->spriteorder[i]].x - mlx->player->pos.x;
	sprite->d_sprite.y =
	sprite->p_sprite[sprite->spriteorder[i]].y - mlx->player->pos.y;
	sprite->invdet =
	1.0 / (mlx->player->plane.x * mlx->player->dir.y
	- mlx->player->dir.x * mlx->player->plane.y);
	sprite->transform.x =
	sprite->invdet * (mlx->player->dir.y *
	sprite->d_sprite.x - mlx->player->dir.x * sprite->d_sprite.y);
	sprite->transform.y =
	sprite->invdet * (-(mlx->player->plane.y)
	* sprite->d_sprite.x + mlx->player->plane.x * sprite->d_sprite.y);
	sprite->spritescreenx = (mlx->screen_width / 2)
	* (1 + sprite->transform.x / sprite->transform.y);
	sprite->sprite_height =
	abs((int)(mlx->screen_height / (sprite->transform.y)));
	sprite->draw_start.y =
	-(sprite->sprite_height) / 2 + mlx->screen_height / 2;
	if (sprite->draw_start.y < 0)
		sprite->draw_start.y = 0;
	sprite->draw_end.y = sprite->sprite_height / 2 + mlx->screen_height / 2;
	if (sprite->draw_end.y >= mlx->screen_height)
		sprite->draw_end.y = mlx->screen_height - 1;
}

void	rollsprite(t_mlx *mlx, t_sprite *sprite)
{
	int		y;
	int		d;

	if (sprite->transform.y > 0 && sprite->stripe > 0 &&
		sprite->stripe < mlx->screen_width &&
		sprite->transform.y < mlx->zbuffer[sprite->stripe])
	{
		y = sprite->draw_start.y;
		while (y < sprite->draw_end.y)
		{
			d = (y) * 256 - mlx->screen_height *
			128 + sprite->sprite_height * 128;
			sprite->tex.y = ((d * TEXHEIGHT) /
			sprite->sprite_height) / 256;
			sprite->color = mlx->texture->sprite
			[(TEXHEIGHT * sprite->tex.y) + sprite->tex.x];
			if ((sprite->color & 0x00FFFFFF) != 0)
				mlx->data[sprite->stripe +
				(y * mlx->screen_width)] = sprite->color;
			y++;
		}
	}
}

void	drawsprite(t_mlx *mlx, t_sprite *sprite)
{
	int			i;

	i = -1;
	while (++i < mlx->spritenbr)
	{
		pre_draw(mlx, sprite, i);
		sprite->sprite_width =
		abs((int)(mlx->screen_height / (sprite->transform.y)));
		sprite->draw_start.x =
		-(sprite->sprite_width) / 2 + sprite->spritescreenx;
		if (sprite->draw_start.x < 0)
			sprite->draw_start.x = 0;
		sprite->draw_end.x = sprite->sprite_width / 2 + sprite->spritescreenx;
		if (sprite->draw_end.x >= mlx->screen_width)
			sprite->draw_end.x = mlx->screen_width - 1;
		sprite->stripe = sprite->draw_start.x;
		while (sprite->stripe < sprite->draw_end.x)
		{
			sprite->tex.x = (int)(256 * (sprite->stripe
			- (-(sprite->sprite_width) / 2 + sprite->spritescreenx))
			* TEXWIDTH / sprite->sprite_width) / 256;
			rollsprite(mlx, sprite);
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
		sqrt(pow(mlx->player->pos.x - sprite->p_sprite[i].x, 2) +
		pow(mlx->player->pos.y - sprite->p_sprite[i].y, 2));
	}
	sortsprite(sprite->spriteorder, sprite->spritedist, mlx->spritenbr, mlx);
	drawsprite(mlx, sprite);
}
