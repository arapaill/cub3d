/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 10:24:20 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/19 12:42:01 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	serpilliere(t_mlx *mlx)
{
	size_t x;

	x = 0;
	//printf("_________TEST_1______\n");
	if (!(mlx->map))
		while (mlx->map[x] != NULL)
			free(mlx->map[x++]);
	//printf("_________TEST_2______\n");
	if (!(mlx->map))
		free(mlx->map);
	//printf("_________TEST_3______\n");
	if (mlx != NULL)
	{
		//printf("_________TEST_4______\n");
		if (!(mlx->zbuffer))
			free(mlx->zbuffer);
		//printf("_________TEST_5______\n");
		if (mlx->frame != NULL)
			mlx_destroy_image(mlx->mlx, mlx->frame);
		//printf("_________TEST_6______\n");
		if (!(mlx->player))
			free(mlx->player);
		//printf("_________TEST_7______\n");
		if (!(mlx->texture))
			free(mlx->texture);
		//printf("_________TEST_8______\n");
		if (!(mlx->sprite))
			free(mlx->sprite);
		//printf("_________TEST_9______\n");
		if (!(mlx->mlx))
			free(mlx->mlx);
		//printf("_________TEST_10______\n");
		free(mlx);
		//printf("_________TEST_11______\n");
	}
	exit (0);
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
	serpilliere(mlx);
}
