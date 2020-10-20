/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 08:47:56 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/20 08:47:33 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static void		bmp_write_pixels(int fd, t_mlx *mlx, unsigned char *bmp_data)
{
	int				height;
	int				width;
	unsigned char	padding[3];
	int				padding_size;
	int				tmp;

	ft_bzero(padding, 3);
	padding_size = (4 - (mlx->screen_width * IMG_DEPTH) % 4) % 4;
	height = mlx->screen_height;
	while (--height >= 0)
	{
		width = -1;
		while (++width < (int)mlx->screen_width)
		{
			tmp = mlx->data[width + (height * mlx->screen_width)];
			bmp_data[3 * width + 2] = tmp / (256 * 256);
			bmp_data[3 * width + 1] = (tmp / 256) % 256;
			bmp_data[3 * width + 0] = tmp % 256;
		}
		write(fd, bmp_data, mlx->screen_width * 3);
		write(fd, padding, padding_size);
	}
}

static int		bmp_write(t_mlx *mlx,
unsigned char *file_header, unsigned char *info_header)
{
	int				fd;
	unsigned char	*bmp_data;

	if ((fd = open(FILENAME, O_WRONLY | O_CREAT, 0644)) < 0)
		return (0);
	if ((bmp_data = malloc(sizeof(unsigned char) *
			(mlx->screen_width * IMG_DEPTH))) == NULL)
		error_manager(3, mlx);
	write(fd, file_header, FILE_HEADER_SIZE);
	write(fd, info_header, INFO_HEADER_SIZE);
	bmp_write_pixels(fd, mlx, bmp_data);
	free(bmp_data);
	close(fd);
	return (1);
}

static void		bmp_header_fill(t_mlx *mlx,
unsigned char *file_header, unsigned char *info_header)
{
	int				file_size;

	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE +
						(IMG_DEPTH * mlx->screen_width +
	((4 - (mlx->screen_width * IMG_DEPTH) % 4) % 4)) * mlx->screen_height;
	ft_bzero(file_header, FILE_HEADER_SIZE);
	ft_bzero(info_header, INFO_HEADER_SIZE);
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
	info_header[0] = (unsigned char)(INFO_HEADER_SIZE);
	info_header[4] = (unsigned char)(mlx->screen_width);
	info_header[5] = (unsigned char)(mlx->screen_width >> 8);
	info_header[6] = (unsigned char)(mlx->screen_width >> 16);
	info_header[7] = (unsigned char)(mlx->screen_width >> 24);
	info_header[8] = (unsigned char)(mlx->screen_height);
	info_header[9] = (unsigned char)(mlx->screen_height >> 8);
	info_header[10] = (unsigned char)(mlx->screen_height >> 16);
	info_header[11] = (unsigned char)(mlx->screen_height >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(IMG_DEPTH * 8);
}

void			bmp_capture(t_mlx *mlx)
{
	unsigned char	file_header[FILE_HEADER_SIZE];
	unsigned char	info_header[INFO_HEADER_SIZE];

	bmp_header_fill(mlx, file_header, info_header);
	if (!(bmp_write(mlx, file_header, info_header)))
		error_manager(5, mlx);
	serpilliere(mlx);
}
