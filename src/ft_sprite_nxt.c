/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_nxt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 09:03:41 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/26 10:30:31 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_cub3d.h"

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
