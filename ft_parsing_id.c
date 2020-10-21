/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_id.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 10:53:29 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/21 11:00:41 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void				text_fc(char c, char *s, t_mlx *mlx, void *texture)
{
	int		i;

	i = 1;
	while (s[i] == ' ')
		i++;
	if (c == 'F')
	{
		if (!(ft_isalpha(s[i])))
			mlx->texture->rgb_floor = fc_atoi(&s[1]);
		else
		{
			mlx->texture->floor =
			(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
		}
	}
	else if (c == 'C')
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

void				text_snwebr(char c, char *s, t_mlx *mlx, void *texture)
{
	int		i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (c == 'S')
		mlx->texture->south =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (c == 'N')
		mlx->texture->north =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (c == 'W')
		mlx->texture->west =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (c == 'E')
		mlx->texture->east =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	if (c == 'B')
	{
		mlx->texture->sprite =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	}
	else if (c == 'R')
		height_width(s, mlx);
}

void				get_texture(char *s, t_mlx *mlx)
{
	size_t	i;
	void	*texture;
	int		a;

	a = 64;
	i = 1;
	while (s[i] == ' ')
		i++;
	if (open(&s[i], O_RDONLY) == -1 && ft_isdigit(s[i]) == 0)
		error_manager(2, mlx);
	texture = mlx_xpm_file_to_image(mlx->mlx, &s[i], &a, &a);
	text_fc(s[0], s, mlx, texture);
	text_snwebr(s[0], s, mlx, texture);
}

int					id_check(t_mlx *mlx, char *line, int fd)
{
	int		i;
	int		ret;
	int		w;

	i = 0;
	ret = 1;
	w = 0;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (line[0] == 'S' || line[0] == 'N' || line[0] == 'E' ||
		line[0] == 'W' || line[0] == 'F' ||
		line[0] == 'C' || line[0] == 'R' || line[0] == 'B')
			get_texture(line, mlx);
		while (line[i] == ' ')
			i++;
		if (line[i] == '1')
		{
			w = ft_strlen(line);
			free(line);
			break ;
		}
		free(line);
	}
	return (w);
}
