/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 10:24:20 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/09 13:48:43 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	serpilliere(t_mlx *mlx)
{
	if (mlx != NULL)
	{
		if (!(mlx->map))
			freemap(mlx->map, 0, mlx);
		if (!(mlx->zbuffer))
			free(mlx->zbuffer);
		if (mlx->frame != NULL)
			mlx_destroy_image(mlx->mlx, mlx->frame);
		if (mlx->player != NULL)
			free(mlx->player);
		if (mlx->texture != NULL)
			free(mlx->texture);
		if (mlx->mlx != NULL)
			free(mlx->mlx);
		if (mlx->sprite != NULL)
			free(mlx->sprite);
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
	serpilliere(mlx);
}
