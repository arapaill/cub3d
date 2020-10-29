/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_id.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 10:53:29 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/29 12:28:10 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_cub3d.h"

void				text_fc(char *s, t_mlx *mlx, void *texture)
{
	int		i;

	i = 1;
	while (s[i] == ' ')
		i++;
	if (s[0] == 'F' && no_double(mlx, s[0]))
	{
		if (!(ft_isalpha(s[i])))
			mlx->texture->rgb_floor = fc_atoi(&s[1], mlx);
		else
		{
			mlx->texture->floor =
			(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
		}
	}
	else if (s[0] == 'C' && no_double(mlx, s[0]))
	{
		if (!(ft_isalpha(s[i])))
			mlx->texture->rgb_ceiling = fc_atoi(&s[1], mlx);
		else
		{
			mlx->texture->ceiling =
			(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
		}
	}
}

void				text_snwebr(char *s, t_mlx *mlx, void *texture)
{
	if (s[0] == 'S' && s[1] == 'O' && no_double(mlx, s[0]))
		mlx->texture->south =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (s[0] == 'N' && s[1] == 'O' && no_double(mlx, s[0]))
		mlx->texture->north =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (s[0] == 'W' && s[1] == 'E' && no_double(mlx, s[0]))
		mlx->texture->west =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (s[0] == 'E' && s[1] == 'A' && no_double(mlx, s[0]))
		mlx->texture->east =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (s[0] == 'S' && s[1] == ' ' && no_double(mlx, 'P'))
		mlx->texture->sprite =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (s[0] == 'R' && s[1] == ' ' && no_double(mlx, s[0]))
		height_width(s, mlx);
	else if (s[0] == 'R' && s[1] != ' ')
		error_manager(2, mlx);
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
	else if (ft_isalpha(line[0]))
		error_manager(2, mlx);
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
		if ((ret = get_next_line(fd, &line)) == -1)
			error_manager(3, mlx);
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
