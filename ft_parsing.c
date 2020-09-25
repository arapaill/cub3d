/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 10:18:10 by arapaill          #+#    #+#             */
/*   Updated: 2020/09/25 15:09:20 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"


char	**creat_world_map(char *file, size_t width, size_t height)
{
	char	*line;
	char	**world_map;
	int		fd;
	int		ret;
	size_t	i;
	size_t	j;

	ret = 1;
	i = 0;
	j = 0;
	world_map = malloc(sizeof(char*) * (height + 1));
	world_map[height] = 0;
	fd = open(file, O_RDONLY);
	////printf("____TEST_PARSING_3____\n");
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		while (*line == ' ')
			line++;
		if (*line == '1')
			break ;
		free(line);
	}
	//printf("____TEST_PARSING_4____\n");
	world_map[i] = malloc(sizeof(char*) * (height + 1));
	while (i < width)
	{
		if (line[i] != 0 && line[i] != '\n')
			world_map[j][i] = line[i];
		else
		{
			while (i < width)
				world_map[j][i++] = ' ';
			break ;
		}
		i++;
	}
	//printf("____TEST_PARSING_5____\n");
	world_map[j++][width] = 0;
	i = 0;
	free(line);
	while (j < height)
	{
		ret = get_next_line(fd, &line);
		world_map[j] = malloc(sizeof(char) * (width + 1));
		while (i < width)
		{
			if (line[i] != 0 && line[i] != '\n')
				world_map[j][i] = line[i];
			else
			{
				while (i < width)
					world_map[j][i++] = ' ';
				break ;
			}
			i++;
		}
		//printf("____TEST_PARSING_6____\n");
		world_map[j++][width] = 0;
		i = 0;
		free(line);
	}
	//printf("____TEST_PARSING_7____\n");
	return (world_map);
}
void	get_texture(char *s, t_mlx *mlx)
{
	size_t	i;
	void	*texture;
	int		a;

	a = 64;
	i = 1;
	while (s[i] == ' ')
		i++;
	if (open(&s[i], O_RDONLY) == -1)
	{
		printf("ERROR NO TEXTURES. 1\n");
		exit(-1);
	}
	texture = mlx_xpm_file_to_image(mlx->mlx, &s[i], &a, &a);
	printf("s[0] = %c\n", s[0]);
	if (s[0] == 'S')
		mlx->texture->south =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (s[0] == 'N')
		mlx->texture->north =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (s[0] == 'W')
		mlx->texture->west =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (s[0] == 'E')
		mlx->texture->east =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else
		printf("ERROR NO TEXTURES. 1\n");
			printf("WEST  :%d\n", (int)(mlx->texture->west));
			printf("EAST  :%d\n", (int)(mlx->texture->east));
			printf("SOUTH :%d\n", (int)(mlx->texture->south));
			printf("NORTH :%d\n", (int)(mlx->texture->north));
}

void    parsing(char *file, t_mlx *mlx)
{
	char	*line;
	int		fd;
	int		ret;
	size_t	w;
	size_t	h;
	size_t	tmp;
	int		i;

	ret = 1;
	w = 0;
	h = 1;
	i = 0;
	fd = open(file, O_RDONLY);
	//printf("____TEST_PARSING_1____\n");
	mlx->texture = malloc(sizeof(t_texture));
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (line[0] == 'S' || line[0] == 'N' || line[0] == 'E' || line[0] == 'W')
			get_texture(line, mlx);
		while (*line == ' ')
			line++;
		if (*line == '1')
		{
			w = ft_strlen(line);
			free(line);
			break ;
		}
		free(line);
	}
	//printf("____TEST_PARSING_2____\n");
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		tmp = ft_strlen(line);
		if (w < tmp)
			w = tmp;
		h++;
		free(line);
	}
	//printf("____TEST_PARSING_1____\n");
	close(fd);
	mlx->map_width = w;
	mlx->map_height = h;
	mlx->map = creat_world_map(file, w, h);
	while (mlx->map[i] != '\0')
	{
		printf("%s\n", mlx->map[i]);
		i++;
	}
}
