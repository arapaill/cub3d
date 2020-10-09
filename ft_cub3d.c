/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:48:38 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/09 10:10:44 by arapaill         ###   ########.fr       */
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
	mlx->frame = mlx_new_image(mlx->mlx, mlx->screen_width, mlx->screen_height);
	mlx->data =
		(int*)mlx_get_data_addr(mlx->frame, &mlx->bpp, &mlx->sl, &mlx->endian);
}

void	RGBA_floor_ceiling(t_mlx *mlx)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < mlx->screen_width)
	{
		while (y < mlx->screen_height / 2)
		{
			mlx->data[x + (y++ * mlx->screen_width)] = mlx->texture->RGB_floor;
			//printf(" y = %d\n", y);
		}
		x++;
		y = 0;
	}
	//printf(" x = %d\n", x);
	x = 0;
	y = mlx->screen_height / 2;
	while (x < mlx->screen_width)
	{
		while (y < mlx->screen_height)
			mlx->data[x + (y++ * mlx->screen_width)] = mlx->texture->RGB_ceiling;
		x++;
		y = mlx->screen_height / 2;
	}
}

void	floor_ceiling(t_mlx *mlx)
{
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	float	posZ;
	float	rowDistance;
	float	floorStepX;
	float	floorStepY;
	float 	floorX;
	float	floorY;
	int		cellX;
	int		cellY;
	int 	tx;
	int 	ty;

	int		color;
	int		p;
	int		y;
	int		x;
	int		h;
	
	y = 0;
	h = mlx->screen_height;
//	printf("text floor : %d, text sky : %d\n", (int)(mlx->texture->floor),(int)(mlx->texture->ceiling));
	//printf("text RGB_floor : %d, text RGB_sky : %d\n", (int)(mlx->texture->RGB_floor),(int)(mlx->texture->RGB_ceiling));
	if(mlx->texture->RGB_floor == 0 && mlx->texture->RGB_ceiling == 0)
	{
		while(++y < h)
			{
				rayDirX0 = mlx->player->dirX - mlx->player->planeX;
				rayDirY0 = mlx->player->dirY - mlx->player->planeY;
				rayDirX1 = mlx->player->dirX + mlx->player->planeX;
				rayDirY1 = mlx->player->dirY + mlx->player->planeY;
				
				 p = y - mlx->screen_height / 2;
				posZ = 0.5 * mlx->screen_height;
				rowDistance = posZ / p;
				
				floorStepX = rowDistance * (rayDirX1 - rayDirX0) / mlx->screen_width;
				floorStepY = rowDistance * (rayDirY1 - rayDirY0) / mlx->screen_width;

				floorX = mlx->player->posX + rowDistance * rayDirX0;
				floorY = mlx->player->posY + rowDistance * rayDirY0;
				x = 0;
				while(++x < (int)(mlx->screen_width))
				{
					cellX = (int)(floorX);
					cellY = (int)(floorY);
					tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
					ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);
					floorX += floorStepX;
					floorY += floorStepY;
					color = mlx->texture->floor[texWidth * ty + tx];
					color = (color >> 1) & 8355711;
					mlx->data[x + (y * mlx->screen_width)] = color;        
					color = mlx->texture->ceiling[texWidth * ty + tx];
					color = (color >> 1) & 8355711;
					mlx->data[x + ((mlx->screen_height - y - 1) * mlx->screen_width)] = color;
				}

			}
	}
	else
		RGBA_floor_ceiling(mlx);
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
	w = mlx->screen_width;
	h = mlx->screen_height;
		if (!(mlx->zbuffer = malloc(sizeof(double *) * mlx->screen_width)))
			error_manager(3);
  while(++x < w)
  {
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
			mlx->data[x - 1 + y * mlx->screen_width] = mlx->color;
		}
		mlx->zbuffer[x] = perpwalldist;
	}

		add_sprites(mlx);
	put_frame(mlx);
	return (0);
}

void	player_init(t_mlx *mlx)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	
	player->posX = 0;
	player->posY = 0;
	player->dirX = -1;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0.86;
	player->sprite_x = -1;
	player->sprite_y = -1;
	mlx->zbuffer = NULL;
	mlx->player = player;
}

void	player_orientation(t_mlx *mlx, int x, int y)
{
	mlx->player->spawnX = x;
	mlx->player->spawnY = y;
	mlx->player->posX = (double)x + 0.5;
	mlx->player->posY = (double)y + 0.5;
	if (mlx->map[x][y] == 'E')
		rot_right(mlx, 1.6);
	if (mlx->map[x][y] == 'S')
		rot_right(mlx, 3.1);
	if (mlx->map[x][y] == 'W')
		rot_right(mlx, 4.7);
	if (mlx->map[x][y] == 'N')
		rot_right(mlx, 6.3);
	mlx->map[x][y] = '0';
}

void check_player_pos(t_mlx *mlx)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < mlx->map_height)
	{
		while (y < mlx->map_width)
		{
			if (mlx->map[x][y] == 'N' || mlx->map[x][y] == 'S' 
			|| mlx->map[x][y] == 'E' || mlx->map[x][y] == 'W')
				player_orientation(mlx, x, y);
			y++;
		}
		y = 0;
		x++;
	}
}


int		main(int argc, char *argv[])
{
	t_mlx	*mlx;

	if(!(mlx = malloc(sizeof(t_mlx))))
		error_manager(3);
	if(!(mlx->sprite = malloc(sizeof(t_sprite))))
		error_manager(3);
	mlx->mlx = mlx_init();
	if (mlx->mlx == 0)
		return (1);
	player_init(mlx);
	if (argc == 2)
		parsing(argv[1], mlx);
	else
		return (1);
	check_player_pos(mlx);
	map_check(mlx);
	parsing_sprite(mlx, mlx->sprite);
	mlx->window = mlx_new_window(mlx->mlx, mlx->screen_width, mlx->screen_height, "ft_cub3D");
	mlx->frame = NULL;
	put_frame(mlx);
	floor_ceiling(mlx);
	raycasting(mlx);
	mlx_hook(mlx->window, 2, 0, key_check, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
