/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_id.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 10:53:29 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/26 10:30:05 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_cub3d.h"

void				text_fc(char *s, t_mlx *mlx, void *texture)
{
	int		i;

	i = 1;
	while (s[i] == ' ')
		i++;
	if (s[0] == 'F')
	{
		if (!(ft_isalpha(s[i])))
			mlx->texture->rgb_floor = fc_atoi(&s[1]);
		else
		{
			mlx->texture->floor =
			(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
		}
	}
	else if (s[0] == 'C')
	{
		if (!(ft_isalpha(s[i])))
			mlx->texture->rgb_ceiling = fc_atoi(&s[1]);
		else
		{
			mlx->texture->ceiling =
			(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
		}
	}
}

void				text_snwebr(char *s, t_mlx *mlx, void *texture)
{
	if (s[0] == 'S' && s[1] == 'O')
		mlx->texture->south =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (s[0] == 'N' && s[1] == 'O')
		mlx->texture->north =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (s[0] == 'W' && s[1] == 'E')
		mlx->texture->west =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (s[0] == 'E' && s[1] == 'A')
		mlx->texture->east =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	if (s[0] == 'S' && s[1] == ' ')
	{
		mlx->texture->sprite =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	}
	else if (s[0] == 'R' && s[1] == ' ')
		height_width(s, mlx);
}

void				id(t_mlx *mlx, char *line)
{
	int		i;

	i = 0;
	if (line == NULL)
		error_manager(6, mlx);
	while (line[i] == ' ')
	{
		i++;
		if (line == NULL)
			error_manager(6, mlx);
	}
	if (line[0] == 'S' || line[0] == 'N' || line[0] == 'E' ||
	line[0] == 'W' || line[0] == 'F' ||
	line[0] == 'C' || line[0] == 'R')
		get_texture(line, mlx);
}

void				id_error(t_mlx *mlx)
{
	if (mlx->texture->south == NULL || mlx->texture->north == NULL
	|| mlx->texture->west == NULL || mlx->texture->east == NULL
	|| mlx->texture->sprite == NULL)
		error_manager(2, mlx);
	if (mlx->texture->floor == NULL && mlx->texture->rgb_floor == 0)
		error_manager(2, mlx);
	if (mlx->texture->ceiling == NULL && mlx->texture->rgb_floor == 0)
		error_manager(2, mlx);
}

void				id_check(t_mlx *mlx, char *line, int fd)
{
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		id(mlx, line);
		while (line[i] == ' ')
			i++;
		if (line[i] == '1')
		{
			free(line);
			break ;
		}
		free(line);
	}
	id_error(mlx);
}
