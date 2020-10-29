/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:55:08 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/29 11:18:34 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_cub3d.h"

void	init_data_sprite(t_mlx *mlx)
{
	mlx->sprite->spriteorder = NULL;
	mlx->sprite->spritedist = NULL;
	mlx->sprite->p_sprite = NULL;
}

void	init_data_pars(t_mlx *mlx)
{
	mlx->pars->line = NULL;
	mlx->pars->world_map = NULL;
}

void	init_data_text(t_mlx *mlx)
{
	mlx->texture->rgb_floor = 0;
	mlx->texture->rgb_ceiling = 0;
	mlx->texture->south = NULL;
	mlx->texture->north = NULL;
	mlx->texture->west = NULL;
	mlx->texture->east = NULL;
	mlx->texture->sprite = NULL;
	mlx->texture->ceiling = NULL;
	mlx->texture->floor = NULL;
}

void	init_data_nxt(t_mlx *mlx)
{
	if (!(mlx->sprite = malloc(sizeof(t_sprite))))
		error_manager(3, mlx);
	init_data_sprite(mlx);
	if (!(mlx->ray = malloc(sizeof(t_ray))))
		error_manager(3, mlx);
	if (!(mlx->fnc = malloc(sizeof(t_fnc))))
		error_manager(3, mlx);
	if (!(mlx->player = malloc(sizeof(t_player))))
		error_manager(3, mlx);
	if (!(mlx->texture = malloc(sizeof(t_texture))))
		error_manager(3, mlx);
	init_data_text(mlx);
	if (!(mlx->pars = malloc(sizeof(t_pars))))
		error_manager(3, mlx);
	init_data_pars(mlx);
}

void	init_data_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->sprite = NULL;
	mlx->ray = NULL;
	mlx->player = NULL;
	mlx->pars = NULL;
	mlx->fnc = NULL;
	mlx->texture = NULL;
	mlx->frame = NULL;
	mlx->window = NULL;
	mlx->map = NULL;
	mlx->data = NULL;
	mlx->zbuffer = NULL;
	mlx->capture = 0;
	init_data_nxt(mlx);
}
