/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:48:38 by arapaill          #+#    #+#             */
/*   Updated: 2020/09/29 16:45:23 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"


void	put_frame(t_mlx *mlx)
{
	if (mlx->frame != NULL)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->frame, 0, 0);
		mlx_destroy_image(mlx->mlx, mlx->frame);
	}
	mlx->frame = mlx_new_image(mlx->mlx, screenWidth, screenHeight);
	mlx->data =
		(int*)mlx_get_data_addr(mlx->frame, &mlx->bpp, &mlx->sl, &mlx->endian);
}

void	RGBA_floor_ceiling(t_mlx *mlx)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < screenWidth)
	{
		while (y < screenHeight / 2)
		{
			mlx->data[x + (y++ * screenWidth)] = RGB_Red;
			//printf(" y = %d\n", y);
		}
		x++;
		y = 0;
	}
	//printf(" x = %d\n", x);
	x = 0;
	y = screenHeight / 2;
	while (x < screenWidth)
	{
		while (y < screenHeight)
			mlx->data[x + (y++ * screenWidth)] = RGB_Blue;
		x++;
		y = screenHeight / 2;
	}
}

void	floor_ceiling(t_mlx *mlx)
{
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	float	posZ;
	float	rowdistance;
	float	floorstepX;
	float	floorstepY;
	float 	floorX;
	float	floorY;
	int		cellX;
	int		cellY;
	int		texX;
	int		texY;
	int		color;
	int		p;
	int		y;
	int		i;
	
	i = 0;
	y = 0;
	if(mlx->texture->floor == 0 && mlx->texture->ceiling == 0)
	{
		while(y++ < screenHeight)
		{
			rayDirX0 = mlx->player->dirX - mlx->player->planeX;
			rayDirY0 = mlx->player->dirY - mlx->player->planeY;
			rayDirX1 = mlx->player->dirX + mlx->player->planeX;
			rayDirY1 = mlx->player->dirY + mlx->player->planeY;
			p = y - screenHeight / 2;
			posZ = 0.5 * screenHeight;
			rowdistance = posZ / p;
			floorstepX = rowdistance * (rayDirX1 - rayDirX0) / screenWidth;
			floorstepY = rowdistance * (rayDirY1 - rayDirY1) / screenWidth;
			floorX = mlx->player->posX + rowdistance * rayDirX0;
			floorY = mlx->player->posY + rowdistance * rayDirY0;
			while(i < screenWidth)
			{
				cellX = (int)(floorX);
				cellY = (int)(floorY);
				texX = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
				texY = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);
				floorX += floorstepX;
				floorY += floorstepY;
				color = mlx->texture->floor[texWidth * texY + texX];
				color = (color >> 1) & 8355711;
				printf("color : %d\n", color);
				mlx->data[i + (y * screenWidth)] = color;
				color = mlx->texture->ceiling[texWidth * texY + texX];
				color = (color >> 1) & 8355711;
				mlx->data[i +((screenHeight - y - 1) * screenWidth)] = color;
				i++;
			}
		}
	}
	else
		RGBA_floor_ceiling(mlx);

	//put_frame(mlx);
}

int raycasting(t_mlx *mlx)
{

	int w;
	int x = 0;
	int y = 0;
	int h;
	int mapx;
	int mapy;
	int stepx;
	int stepy;
	int hit;
	int side;
	int lineheight;
	int drawstart;
	int drawend;
	double camerax;
	double raydirx;
	double raydiry;
	double sidedistx;
	double sidedisty;
	double deltadistx;
	double deltadisty;
	double perpwalldist;
	double wallX;
	int texX;
	double step;
	double texPos;
	int texY;
	hit = 0;
	w = screenWidth;
	h = screenHeight;
  while(x < w)
  {
	  //floor_ceiling(mlx);
		camerax = 2 * x / (double)w - 1;
		raydirx = mlx->player->dirX + mlx->player->planeX * camerax;
		raydiry = mlx->player->dirY + mlx->player->planeY * camerax;

		mapx = (int)mlx->player->posX;
		mapy = (int)mlx->player->posY;

		deltadistx = (raydiry == 0) ? 0 : ((raydirx == 0) ? 1 : fabs(1 / raydirx));
		deltadisty = (raydirx == 0) ? 0 : ((raydiry == 0) ? 1 : fabs(1 / raydiry));

		hit = 0;

		if (raydirx < 0)
		{
			stepx = -1;
			sidedistx = (mlx->player->posX - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (mapx + 1.0 - mlx->player->posX) * deltadistx;
		}
		if (raydiry < 0)
		{
			stepy = -1;
			sidedisty = (mlx->player->posY - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (mapy + 1.0 - mlx->player->posY) * deltadisty;
		}

		while (hit == 0)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
			}
			if (mlx->map[(int)mapx][(int)mapy] > '0')
				hit = 1;
		}
		if (side == 0)
			perpwalldist =
				(mapx - mlx->player->posX + (1 - stepx) / 2) / raydirx;
		else
			perpwalldist =
				(mapy - mlx->player->posY + (1 - stepy) / 2) / raydiry;

		lineheight = (int)(h / perpwalldist);
		drawstart = -lineheight / 2 + h / 2;
		if (drawstart < 0)
			drawstart = 0;
		drawend = lineheight / 2 + h / 2;
		if (drawend >= h)
			drawend = h - 1;

		if (side == 0)
			wallX = mlx->player->posY + perpwalldist * raydiry;
		else
			wallX = mlx->player->posX + perpwalldist * raydirx;
		wallX -= floor((wallX));

		texX = (int)(wallX * (double)texWidth);
		if (side == 0 && raydirx > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && raydiry < 0)
			texX = texWidth - texX - 1;

		step = 1.0 * texHeight / lineheight;
		texPos = (drawstart - h / 2 + lineheight / 2) * step;
		for (y = drawstart; y < drawend; y++)
		{
			texY = (int)texPos & (texHeight - 1);
			texPos += step;
			if (side == 1)
			{
				if (raydiry >= 0)
					mlx->color = mlx->texture->west[(texHeight * texY) + texX];
				else
					mlx->color = mlx->texture->east[(texHeight * texY) + texX];
			}
			else
			{
				if (raydirx >= 0)
					mlx->color = mlx->texture->north[(texHeight * texY) + texX];
				else
					mlx->color = mlx->texture->south[(texHeight * texY) + texX];
			}
			mlx->data[x - 1 + y * screenWidth] = mlx->color;
		}
	x++;
	}
	put_frame(mlx);
	return (0);
}

void	player_init(t_mlx *mlx)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	player->posX = 21;
	player->posY = 12;
	player->dirX = -1;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0.86;
	mlx->player = player;
}


int		main(int argc, char *argv[])
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	if (mlx->mlx == 0)
		return (1);
	player_init(mlx);
	if (argc == 2)
		parsing(argv[1], mlx);
	else
		return (1);
	mlx->window = mlx_new_window(mlx->mlx, screenWidth, screenHeight, "ft_Cub3D");
	mlx->frame = NULL;
	put_frame(mlx);
	floor_ceiling(mlx);
	raycasting(mlx);
	mlx_hook(mlx->window, 2, 0, key_check, mlx);
	mlx_loop(mlx->mlx);
	free(mlx);
	return (0);
}
