/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 09:43:29 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/26 10:30:01 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_cub3d.h"

void	size_file(t_mlx *mlx, char *file)
{
	int		fd;
	int		ret;
	char	*line;
	int		w;
	int		i;

	fd = open(file, O_RDONLY);
	ret = 1;
	i = 0;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		while (line[i] == ' ')
			i++;
		if (line[i] == '1')
		{
			if (w < (int)ft_strlen(line))
				w = ft_strlen(line);
		}
		free(line);
	}
	close(fd);
	mlx->map_width = w;
}

void	fill_map_nxt(t_mlx *mlx, t_pars *pars, int i, int j)
{
	while (j < mlx->map_height)
	{
		pars->ret = get_next_line(pars->fd, &pars->line);
		if (!(pars->world_map[j] = malloc(sizeof(char) * (mlx->map_width + 1))))
			error_manager(3, mlx);
		while (i < mlx->map_width)
		{
			if (pars->line[i] != 0 && pars->line[i] != '\n')
				pars->world_map[j][i] = pars->line[i];
			else
			{
				while (i < mlx->map_width)
					pars->world_map[j][i++] = ' ';
				break ;
			}
			i++;
		}
		pars->world_map[j++][mlx->map_width] = 0;
		i = 0;
		free(pars->line);
	}
}

void	space_map(t_mlx *mlx, t_pars *pars)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < mlx->map_width)
	{
		if (pars->line[i] != 0 && pars->line[i] != '\n')
			pars->world_map[j][i] = pars->line[i];
		else
		{
			while (i < mlx->map_width)
				pars->world_map[j][i++] = ' ';
			break ;
		}
		i++;
	}
	pars->world_map[j++][mlx->map_width] = 0;
	free(pars->line);
	i = 0;
	fill_map_nxt(mlx, pars, i, j);
}

void	fill_map(t_mlx *mlx, t_pars *pars)
{
	int		i;

	i = 0;
	while (pars->ret == 1)
	{
		pars->ret = get_next_line(pars->fd, &pars->line);
		while (pars->line[i] == ' ')
			i++;
		if (pars->line[i] == '1')
			break ;
		free(pars->line);
	}
	i = 0;
	if (!(pars->world_map[i] = malloc(sizeof(char*) * (mlx->map_height + 1))))
		error_manager(3, mlx);
}

char	**creat_world_map(char *file, t_mlx *mlx)
{
	t_pars	*pars;
	int		i;
	int		j;

	if (!(mlx->pars = malloc(sizeof(t_pars))))
		error_manager(3, mlx);
	pars = mlx->pars;
	if (!(pars->world_map = malloc(sizeof(char*) * (mlx->map_height + 1))))
		error_manager(3, mlx);
	pars->fd = open(file, O_RDONLY);
	pars->world_map[mlx->map_height] = 0;
	pars->ret = 1;
	i = 0;
	j = 0;
	fill_map(mlx, pars);
	space_map(mlx, pars);
	return (pars->world_map);
}
