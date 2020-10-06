/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:23:53 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/06 15:57:41 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"



void sortSprites(int* order, double* dist, int amount)
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

  std::sort(sprites.begin(), sprites.end());
  // restore in reverse order to go from farthest to nearest
  for(int i = 0; i < amount; i++) {
    dist[i] = sprites[amount - i - 1].first;
    order[i] = sprites[amount - i - 1].second;
  }
}
}




int     add_sprites(t_mlx *mlx)
{
	
	int     i;

	i = -1;
	while(++i < mlx->spritenbr)
	{
		sprite->spriteorder[i] = i;
		sprite->spritedist[i] = ((mlx->player->posX - p_sprite[i].x) * 2 + (mlx->player->posY - p_sprite[i].y) * 2)
	}
	
}
spriteDistance[i] = ((posX - sprite[i].x) * (posX - sprite[i].x) +
(posY - sprite[i].y) * (posY - sprite[i].y)); //sqrt not taken, unneeded