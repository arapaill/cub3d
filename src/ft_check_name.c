/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 09:59:52 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/29 10:06:43 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_cub3d.h"

void	check_name(t_mlx *mlx, char *s)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != '.')
		i++;
	if (s[i] && s[i] == '.')
		if (ft_strncmp(&s[i], ".cub\0", 5) != 0)
			error_manager(6, mlx);
}

int		no_double(t_mlx *mlx, char c)
{
	if (c == 'S')
		if (mlx->texture->south != NULL)
			error_manager(2, mlx);
	if (c == 'N')
		if (mlx->texture->north != NULL)
			error_manager(2, mlx);
	if (c == 'W')
		if (mlx->texture->west != NULL)
			error_manager(2, mlx);
	if (c == 'E')
		if (mlx->texture->east != NULL)
			error_manager(2, mlx);
	if (c == 'P')
		if (mlx->texture->sprite != NULL)
			error_manager(2, mlx);
	if (c == 'R')
		if (mlx->screen_height != 0)
			error_manager(2, mlx);
	if (c == 'F')
		if (mlx->texture->floor != NULL || mlx->texture->rgb_ceiling != 0)
			error_manager(2, mlx);
	if (c == 'C')
		if (mlx->texture->ceiling != NULL || mlx->texture->rgb_ceiling != 0)
			error_manager(2, mlx);
	return (1);
}
