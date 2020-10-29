/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 10:24:20 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/29 10:46:14 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_cub3d.h"

void	serpilliere(t_mlx *mlx)
{
	size_t x;

	x = 0;
	if (mlx)
	{
		if (mlx->map)
			while (mlx->map && mlx->map[x])
				free(mlx->map[x++]);
		if (mlx->map)
			free(mlx->map);
		if (mlx->zbuffer)
			free(mlx->zbuffer);
		if (mlx->frame)
			mlx_destroy_image(mlx->mlx, mlx->frame);
		if (mlx->player)
			free(mlx->player);
		if (mlx->texture)
			free(mlx->texture);
		if (mlx->sprite)
			free(mlx->sprite);
		if (mlx->mlx)
			free(mlx->mlx);
		free(mlx);
	}
	exit(0);
}

void	error_manager(int error, t_mlx *mlx)
{
	if (error == 1)
		ft_putstr_fd("MAP ERROR\n", 1);
	else if (error == 2)
		ft_putstr_fd("TEXTURES OR RGBA COLOR ERROR\n", 1);
	else if (error == 3)
		ft_putstr_fd("MALLOC ERROR\n", 1);
	else if (error == 4)
		ft_putstr_fd("PLAYER POSITION ERROR\n", 1);
	else if (error == 5)
		ft_putstr_fd("CAPTURE ERROR\n", 1);
	else if (error == 6)
		ft_putstr_fd("ARGUMENTS ERROR\n", 1);
	else if (error == 7)
		ft_putstr_fd("RESOLUTION ERROR\n", 1);
	serpilliere(mlx);
}
