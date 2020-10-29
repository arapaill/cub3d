/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 10:24:20 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/29 12:20:15 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_cub3d.h"

void	free_sprite(t_mlx *mlx)
{
	if (!(mlx->sprite))
		return ;
	if (mlx->sprite->spriteorder)
		free(mlx->sprite->spriteorder);
	if (mlx->sprite->spritedist)
		free(mlx->sprite->spritedist);
	if (mlx->sprite->p_sprite)
		free(mlx->sprite->p_sprite);
	free(mlx->sprite);
}

void	free_pars(t_mlx *mlx)
{
	size_t	x;

	x = 0;
	if (!(mlx->pars))
		return ;
	if (mlx->pars->line)
		free(mlx->pars->line);
	free(mlx->pars);
}

void	free_text(t_mlx *mlx)
{
	free_sprite(mlx);
	free_pars(mlx);
	if (!(mlx->texture))
		return ;
	if (mlx->texture->south)
		free(mlx->texture->south);
	if (mlx->texture->north)
		free(mlx->texture->north);
	if (mlx->texture->west)
		free(mlx->texture->west);
	if (mlx->texture->east)
		free(mlx->texture->east);
	if (mlx->texture->sprite)
		free(mlx->texture->sprite);
	if (mlx->texture->ceiling)
		free(mlx->texture->ceiling);
	if (mlx->texture->floor)
		free(mlx->texture->floor);
	if (mlx->ray)
		free(mlx->ray);
	free(mlx->texture);
	free(mlx);
}

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
		if (mlx->mlx)
			free(mlx->mlx);
		if (mlx->fnc)
			free(mlx->fnc);
		free_text(mlx);
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
