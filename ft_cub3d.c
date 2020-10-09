/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:48:38 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/09 16:02:20 by arapaill         ###   ########.fr       */
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
			mlx->data[x + (y++ * mlx->screen_width)] = mlx->texture->rgb_floor;
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
			mlx->data[x + (y++ * mlx->screen_width)] = mlx->texture->rgb_ceiling;
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
	//printf("text rgb_floor : %d, text RGB_sky : %d\n", (int)(mlx->texture->rgb_floor),(int)(mlx->texture->rgb_ceiling));
	if(mlx->texture->rgb_floor == 0 && mlx->texture->rgb_ceiling == 0)
	{
		while(++y < h)
			{
				rayDirX0 = mlx->player->dir.x - mlx->player->plane.x;
				rayDirY0 = mlx->player->dir.y - mlx->player->plane.y;
				rayDirX1 = mlx->player->dir.x + mlx->player->plane.x;
				rayDirY1 = mlx->player->dir.y + mlx->player->plane.y;
				
				 p = y - mlx->screen_height / 2;
				posZ = 0.5 * mlx->screen_height;
				rowDistance = posZ / p;
				
				floorStepX = rowDistance * (rayDirX1 - rayDirX0) / mlx->screen_width;
				floorStepY = rowDistance * (rayDirY1 - rayDirY0) / mlx->screen_width;

				floorX = mlx->player->pos.x + rowDistance * rayDirX0;
				floorY = mlx->player->pos.y + rowDistance * rayDirY0;
				x = 0;
				while(++x < (int)(mlx->screen_width))
				{
					cellX = (int)(floorX);
					cellY = (int)(floorY);
					tx = (int)(TEXWIDTH * (floorX - cellX)) & (TEXWIDTH - 1);
					ty = (int)(TEXHEIGHT * (floorY - cellY)) & (TEXHEIGHT - 1);
					floorX += floorStepX;
					floorY += floorStepY;
					color = mlx->texture->floor[TEXWIDTH * ty + tx];
					color = (color >> 1) & 8355711;
					mlx->data[x + (y * mlx->screen_width)] = color;        
					color = mlx->texture->ceiling[TEXWIDTH * ty + tx];
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
			error_manager(3, mlx);
  while(++x < w)
  {
		camerax = 2 * x / (double)w - 1;
		raydirx = mlx->player->dir.x + mlx->player->plane.x * camerax;
		raydiry = mlx->player->dir.y + mlx->player->plane.y * camerax;

		mapx = (int)mlx->player->pos.x;
		mapy = (int)mlx->player->pos.y;

		deltadistx = (raydiry == 0) ? 0 : ((raydirx == 0) ? 1 : fabs(1 / raydirx));
		deltadisty = (raydirx == 0) ? 0 : ((raydiry == 0) ? 1 : fabs(1 / raydiry));

		hit = 0;

		if (raydirx < 0)
		{
			stepx = -1;
			sidedistx = (mlx->player->pos.x - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (mapx + 1.0 - mlx->player->pos.x) * deltadistx;
		}
		if (raydiry < 0)
		{
			stepy = -1;
			sidedisty = (mlx->player->pos.y - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (mapy + 1.0 - mlx->player->pos.y) * deltadisty;
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
				(mapx - mlx->player->pos.x + (1 - stepx) / 2) / raydirx;
		else
			perpwalldist =
				(mapy - mlx->player->pos.y + (1 - stepy) / 2) / raydiry;

		lineheight = (int)(h / perpwalldist);
		drawstart = -lineheight / 2 + h / 2;
		if (drawstart < 0)
			drawstart = 0;
		drawend = lineheight / 2 + h / 2;
		if (drawend >= h)
			drawend = h - 1;

		if (side == 0)
			wallX = mlx->player->pos.y + perpwalldist * raydiry;
		else
			wallX = mlx->player->pos.x + perpwalldist * raydirx;
		wallX -= floor((wallX));

		texX = (int)(wallX * (double)TEXWIDTH);
		if (side == 0 && raydirx > 0)
			texX = TEXWIDTH - texX - 1;
		if (side == 1 && raydiry < 0)
			texX = TEXWIDTH - texX - 1;

		step = 1.0 * TEXHEIGHT / lineheight;
		texPos = (drawstart - h / 2 + lineheight / 2) * step;
		for (y = drawstart; y < drawend; y++)
		{
			texY = (int)texPos & (TEXHEIGHT - 1);
			texPos += step;
			if (side == 1)
			{
				if (raydiry >= 0)
					mlx->color = mlx->texture->west[(TEXHEIGHT * texY) + texX];
				else
					mlx->color = mlx->texture->east[(TEXHEIGHT * texY) + texX];
			}
			else
			{
				if (raydirx >= 0)
					mlx->color = mlx->texture->north[(TEXHEIGHT * texY) + texX];
				else
					mlx->color = mlx->texture->south[(TEXHEIGHT * texY) + texX];
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
	
	player->pos.x = 0;
	player->pos.y = 0;
	player->dir.x = -1;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0.86;
	mlx->zbuffer = NULL;
	mlx->player = player;
}

void	player_orientation(t_mlx *mlx, int x, int y)
{
	if(mlx->player->spawn.x == -1)
	{
		mlx->player->spawn.x = x;
		mlx->player->spawn.y = y;
	}
	else
		error_manager(4, mlx);
	mlx->player->pos.x = (double)x + 0.5;
	mlx->player->pos.y = (double)y + 0.5;
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
	mlx->player->spawn.x = -1;
	mlx->player->spawn.y = -1;
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
		if (mlx->player->spawn.x == -1 || mlx->player->spawn.y == -1)
		error_manager(4, mlx);
}


int		main(int argc, char *argv[])
{
	t_mlx	*mlx;

	if(!(mlx = malloc(sizeof(t_mlx))))
		error_manager(3, mlx);
	if(!(mlx->sprite = malloc(sizeof(t_sprite))))
		error_manager(3, mlx);
	mlx->mlx = mlx_init();
	mlx->frame = NULL;
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
	put_frame(mlx);
	floor_ceiling(mlx);
	raycasting(mlx);
	mlx_hook(mlx->window, 2, 0, key_check, mlx);
	mlx_hook(mlx->window, 17L, 0, (int (*)())(serpilliere), mlx);
	mlx_loop(mlx->mlx);
	serpilliere(mlx);
	return (0);
}
