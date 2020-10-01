/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 10:18:10 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/01 15:40:22 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"


static char	**creat_world_map(char *file, size_t width, size_t height)
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
	//printf("____TEST_PARSING_4____\n");
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		while (line[i] == ' ')
			i++;
		if (line[i] == '1')
			break ;
		free(line);
	}
	i = 0;
	//printf("____TEST_PARSING_5____\n");
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
	//printf("____TEST_PARSING_6____\n");
	world_map[j++][width] = 0;
	//free(line);
	i = 0;
	//printf("____TEST_PARSING_A____\n");
	while (j < height)
	{
		ret = get_next_line(fd, &line);
		//printf("____TEST_PARSING_B____\n");
		world_map[j] = malloc(sizeof(char) * (width + 1));
		while (i < width)
		{
			//printf("____TEST_PARSING_C____\n");
			if (line[i] != 0 && line[i] != '\n')
				world_map[j][i] = line[i];
			else
			{
				//printf("____TEST_PARSING_D____\n");
				while (i < width)
					world_map[j][i++] = ' ';
				break ;
			}
			i++;
		}
		//printf("____TEST_PARSING_7____\n");
		world_map[j++][width] = 0;
		i = 0;
		free(line);
	}
	//printf("____TEST_PARSING_8____\n");
	for(size_t x = 0; x < height; x++)
	{
		for(size_t y = 0; y < width; y++)
			printf("%c", world_map[x][y]);
		printf("\n");
	}
	
	return (world_map);
}

int			fc_atoi(char *s)
{
	int		i;
	int		r;
	int		g;
	int		b;

	i = 0;
	while (s[i] == ' ')
		i++;
	r = ft_atoi(&s[i]);
	while (ft_isdigit(s[i]) || s[i] == ' ')
		i++;
	g = ft_atoi(&s[++i]);
	while (ft_isdigit(s[i]) || s[i] == ' ')
		i++;
	b = ft_atoi(&s[++i]);
	//printf("r = %d, g = %d, b = %d \n", r, g, b);
	//printf("____TEST_PARSING_9____\n");
	return (r + (g * 256) + (b * 256 * 256));
}

void	height_width(char *s, t_mlx *mlx)
{
	size_t i;

	i = 1;
	while (s[i] == ' ')
		i++;
	mlx->screen_width = ft_atoi(&s[i]);
	while (ft_isdigit(s[i]))
		i++;
	while (s[i] != ' ')
		i++;
	mlx->screen_height = ft_atoi(&s[i]);
	if (mlx->screen_width > 2560)
		mlx->screen_width = 2560;
	if (mlx->screen_height > 1440)
		mlx->screen_height = 1440;
		//printf("____TEST_PARSING_10____\n");
	//printf("W : %d\nH : %d\n", mlx->screen_width, mlx->screen_height);
}

static void	get_texture(char *s, t_mlx *mlx)
{
	size_t	i;
	void	*texture;
	int		a;

	a = 64;
	i = 1;
	while (s[i] == ' ')
		i++;
	//printf("s[0] = %c\n", s[0]);
	if (open(&s[i], O_RDONLY) == -1 && ft_isdigit(s[i]) == 0)
	{
		printf("ERROR NO TEXTURES.\n");
		exit(-1);
	}
	texture = mlx_xpm_file_to_image(mlx->mlx, &s[i], &a, &a);
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
	else if (s[0] == 'F')
	{
		if (!(ft_isalpha(s[i])))
			mlx->texture->RGB_floor = fc_atoi(&s[1]);
		else
		{
			mlx->texture->floor =
			(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
			mlx->texture->RGB_floor = 0;
		}
	}
	else if (s[0] == 'C')
	{
		if (!(ft_isalpha(s[i])))
			mlx->texture->RGB_ceiling = fc_atoi(&s[1]);
		else
		{
			mlx->texture->ceiling =
			(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
			mlx->texture->RGB_ceiling = 0;
		}
	}
	if (s[0] == 'R')
		height_width(s, mlx);
	//	printf("____TEST_PARSING_11____\n");
}

void			parsing(char *file, t_mlx *mlx)
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
		if (line[0] == 'S' || line[0] == 'N' || line[0] == 'E' ||
		line[0] == 'W' || line[0] == 'F' || line[0] == 'C' || line[0] == 'R')
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
	//printf("____TEST_PARSING_3____\n");
	close(fd);
	mlx->map_width = w;
	mlx->map_height = h;
	mlx->map = creat_world_map(file, w, h);
}
