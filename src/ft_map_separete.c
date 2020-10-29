/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_separete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:27:27 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/29 12:36:21 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_cub3d.h"

void		map_separete_nxt(t_mlx *mlx, char *line, int fd)
{
	t_point	is_map;
	int		i;
	int		ret;

	i = 0;
	is_map.x = 0;
	is_map.y = 0;
	ret = 1;
	while (ret == 1)
	{
		if ((ret = get_next_line(fd, &line)) == -1)
			error_manager(3, mlx);
		while (line[i] == ' ')
			i++;
		if (line[i] == '1')
			is_map.x = 1;
		if (is_map.x == 1)
		{
			if (line[i] == '\0')
				is_map.y = 1;
			if (is_map.y == 1 && line[i] == '1')
				error_manager(1, mlx);
		}
		free(line);
	}
}

void		map_separete(t_mlx *mlx, char *file)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(file, O_RDONLY);
	map_separete_nxt(mlx, line, fd);
	close(fd);
}
