/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 09:58:24 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/06 15:57:46 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		freemap(char **map, int n, t_mlx *mlx)
{
	int		i;

	i = -1;
	while (++i < mlx->map_height)
	{
		free(map[i]);
		map[i] = NULL;
	}
	free(map);
	map = NULL;
	if (n != 0)
		error_manager(n);
	return (n);
}

void	visit_neighboor(char **map, t_point size, t_point start, t_point nbr)
{
	map[start.x][start.y] = '3';
	if (start.x > 0 && map[start.x - 1][start.y] == '0')
	{
		nbr.x = start.x - 1;
		nbr.y = start.y;
		visit_neighboor(map, size, nbr, start);
	}
	if (start.x < (size.x - 1) && map[start.x + 1][start.y] == '0')
	{
		nbr.x = start.x + 1;
		nbr.y = start.y;
		visit_neighboor(map, size, nbr, start);
	}
	if (start.y > 0 && map[start.x][start.y - 1] == '0')
	{
		nbr.x = start.x;
		nbr.y = start.y - 1;
		visit_neighboor(map, size, nbr, start);
	}
	if (start.y < (size.y - 1) && map[start.x][start.y + 1] == '0')
	{
		nbr.x = start.x;
		nbr.y = start.y + 1;
		visit_neighboor(map, size, nbr, start);
	}
}

int		map_error(t_mlx *mlx, char **map)
{
	int i;
	int j;

	i = -1;
	while (++i < mlx->map_height)
	{
		j = -1;
		while (++j < mlx->map_width)
		{
			if (map[i][j] == '2')
				mlx->spritenbr++;
			if (map[i][j] < '0' || map[i][j] > '3')
				return (freemap(map, 1, mlx));
			if (map[i][j] == '3' && (i == 0 || i ==
				mlx->map_height - 1 || j == 0 || j == mlx->map_width - 1))
				return (freemap(map, 1, mlx));
		}
	}
	return (freemap(map, 0, mlx));
}

int		map_check(t_mlx *mlx)
{
	char	**cp_map;
	int		x;
	int		y;
	t_point	start;
	t_point	size;

	start.x = mlx->player->spawnX;
	start.y = mlx->player->spawnY;
	size.x = mlx->map_height;
	size.y = mlx->map_width;
	if (!(cp_map = (char **)malloc((sizeof(char *) * mlx->map_height) + 1)))
		error_manager(3);
	x = -1;
	while (++x < mlx->map_height)
	{
		if (!(cp_map[x] = (char *)malloc((sizeof(char) * mlx->map_width) + 1)))
			error_manager(3);
		y = -1;
		while (++y < mlx->map_width)
		{
			cp_map[x][y] = mlx->map[x][y];
			if (cp_map[x][y] == ' ')
				cp_map[x][y] = '0';
		}
	}
	visit_neighboor(cp_map, size, start, start);
	return (map_error(mlx, cp_map));
}
