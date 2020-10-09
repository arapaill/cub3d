/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_sprite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:50:17 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/09 10:31:21 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	pinpoint_sprite(t_mlx *mlx, t_sprite *sprite)
{
	int		i;
	int		j;
	int		nb;

	i = -1;
	nb = 0;
	while (++i < mlx->map_height)
	{
		j = -1;
		while (++j < mlx->map_width)
			if (mlx->map[i][j] == '2')
			{
				sprite->p_sprite[nb].x = i + 0.5;
				sprite->p_sprite[nb].y = j + 0.5;
				mlx->map[i][j] = '0';
				nb++;
			}
	}
}

void	parsing_sprite(t_mlx *mlx, t_sprite *sprite)
{
	if (!(sprite->spriteorder = malloc(sizeof(int) * mlx->spritenbr)))
		error_manager(3);
	if (!(sprite->spritedist = malloc(sizeof(double) * mlx->spritenbr)))
		error_manager(3);
	if (!(sprite->p_sprite = malloc(sizeof(t_double) * mlx->spritenbr)))
		error_manager(3);
	pinpoint_sprite(mlx, sprite);
}
