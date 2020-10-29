/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 10:18:10 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/29 11:06:39 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_cub3d.h"

int				fc_atoi(char *s, t_mlx *mlx)
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
	if (s[i] != ',')
		error_manager(2, mlx);
	g = ft_atoi(&s[++i]);
	while (ft_isdigit(s[i]) || s[i] == ' ')
		i++;
	if (s[i] != ',')
		error_manager(2, mlx);
	b = ft_atoi(&s[++i]);
	while (ft_isdigit(s[i]) || s[i] == ' ')
		i++;
	if (r > 255 || g > 255 || b > 255 ||
	r < 0 || g < 0 || b < 0 || s[i])
		error_manager(2, mlx);
	return (r + (g * 256) + (b * 256 * 256));
}

void			height_width(char *s, t_mlx *mlx)
{
	size_t i;

	i = 1;
	while (s[i] == ' ')
		i++;
	mlx->screen_width = ft_atoi(&s[i]);
	while (ft_isdigit(s[i]))
		i++;
	mlx->screen_height = ft_atoi(&s[i]);
	if (mlx->screen_width > 2560)
		mlx->screen_width = 2560;
	if (mlx->screen_height > 1440)
		mlx->screen_height = 1440;
	if (mlx->screen_height < 1)
		error_manager(7, mlx);
	if (mlx->screen_width < 1)
		error_manager(7, mlx);
}

int				gnl(char *line, int fd, int w)
{
	int		h;
	int		tmp;
	int		ret;

	ret = 1;
	h = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		tmp = ft_strlen(line);
		if (w < tmp)
			w = tmp;
		h++;
		if (line)
			free(line);
	}
	return (h);
}

void			get_texture(char *s, t_mlx *mlx)
{
	size_t	i;
	void	*texture;
	int		a;

	a = 64;
	i = 2;
	while (s[i] == ' ')
		i++;
	if (open(&s[i], O_RDONLY) == -1 && ft_isdigit(s[i]) == 0)
		error_manager(2, mlx);
	texture = mlx_xpm_file_to_image(mlx->mlx, &s[i], &a, &a);
	text_fc(s, mlx, texture);
	text_snwebr(s, mlx, texture);
}

void			parsing(char *file, t_mlx *mlx)
{
	char	*line;
	int		fd;
	int		h;

	size_file(mlx, file);
	fd = open(file, O_RDONLY);
	line = NULL;
	id_check(mlx, line, fd);
	h = gnl(line, fd, mlx->map_width);
	close(fd);
	mlx->map_height = h;
	mlx->map = creat_world_map(file, mlx);
}
