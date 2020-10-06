/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:23:53 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/06 16:59:56 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"


void	ordersprites(t_sort *sprite, int amount, double *dist)
{
	t_sort	buff;
	int		i;
	int		j;

	i = -1;
	j = 1;

	while (++i < amount)
	{
		while (dist[i] < dist[j])
		{
			buff = sprite[i];
			sprite[i] = sprite[j];
			sprite[j] = buff;
			j++;
		}
	}
}

void	sortsprite(int* order, double* dist, int amount)
{
  t_sort	*sprite;
  int		i;

  if(!(sprite = malloc(sizeof(t_sort) * amount)))
		error_manager(3);
	i = -1;
	while(++i < amount)
	{
		sprite[i].first = dist[i];
		sprite[i]. second = order[i];
	}
	i = -1;
	ordersprites(sprite, amount, dist);
	while (++i < amount)
	{
		dist[i] = sprite[i].first;
    	order[i] = sprite[i].second;
	}
}

drawsprite()

void    add_sprites(t_mlx *mlx)
{
	
	int     i;
	t_sprite *sprite;
	
	if(!(sprite = malloc(sizeof(t_sprite))))
		error_manager(3);
	parsing_sprite(mlx, sprite);
	i = -1;
	while(++i < mlx->spritenbr)
	{
		sprite->spriteorder[i] = i;
		sprite->spritedist[i] = ((mlx->player->posX - sprite->p_sprite[i].x) * 2
		+ (mlx->player->posY - sprite->p_sprite[i].y) * 2);
	}
	sortsprite(sprite->spriteorder, sprite->spritedist, mlx->spritenbr);
	drawsprite(sprite);
}
//spriteDistance[i] = ((posX - sprite[i].x) * (posX - sprite[i].x) +
//(posY - sprite[i].y) * (posY - sprite[i].y)); //sqrt not taken, unneeded