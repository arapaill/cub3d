/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 10:18:10 by arapaill          #+#    #+#             */
/*   Updated: 2020/09/17 12:56:33 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

char **creat_world_map(char *file size_t width, size_t height)
{
	char	*line;
	char	**world_map;
	int		fd;
	int		ret;
	size_t	i;
	size_t	j;

	ret = 1;
	world_map = malloc(sizeof(char*) * (height + 1));
	world_map[height] = 0;
	fd = open(O_RDONLY);
	while(ret == 1)
	{
		ret = get_next_line(fd, &line)
		while (*line == ' ')
			line++;
		if (*line == '1')
			break ;
		free(line);
	}
	world_map[i] = malloc(sizeof(char*) * (height + 1));
	while (i < width)
	{
		if (line[i] != 0 && line[i] != '\n')
			world_map[k][i] = line[i];
		else
		{
			while (i < width)
				world_map[k][i++] = ' ';
			break ;
		}
		i++;
	}
	world_map[k++][width] = 0;
	i = 0;
	free (line)
	while (k < height)
	{
		ret = get_next_line(fd, &line);
		world_map[k] = malloc(sizeof(char) * (width + 1));
		while (i < width)
		{
			if (line[i] != 0 && line[i] != '\n')
				world_map[k][i] = line[i];
			else
			{
				while (i < width)
					world_map[k][i++] = ' ';
				break ;
			}
			i++;
		}
		world_map[k++][width] = 0;
		i = 0;
		free(line);
	}
	return (world_map);
}

void    parsing(char *file, t_mlx *mlx)
{
	char	*line;
	int		fd;
	int		ret;
	size_t	w;
	size_t	h;
	size_t	tmp;

	ret = 1;
	w = 0;
	h = 1;
	fd = open(file, O_RDONLY);
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		while (*line == ' ')
			line++;
		if (*line == '1')
		{
			w = ft_strlen(line)
			free(line);
			break ;
		}
		free (line);
	}
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		tmp = ft_strlen(line);
		if (w < tmp)
			w = tmp;
		h++;
		free(line);
	}
	close(fd)
	mlx->map_width = w;
	mlx->map_height = h;
	mlx->map = mllc_world_map(file, width, height);
}
