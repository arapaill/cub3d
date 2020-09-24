/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:48:38 by arapaill          #+#    #+#             */
/*   Updated: 2020/09/24 10:10:29 by arapaill         ###   ########.fr       */
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
		printf("%d\n", mlx->bpp);
}

/*
int worldMap[mapWidth][mapHeight]=  
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},-+++++++++++++++99
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
*/
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
	//length of ray from current position to next x or y-side
	double sidedistx;
	double sidedisty;
	double deltadistx;
	double deltadisty;
	double perpwalldist;
	double moveSpeed;
	double rotSpeed;
	double wallX;
	int texX;
	double step;
	double texPos;
	int texY;
	//double oldDirX;
	//double oldPlaneX;
	hit = 0;
	w = screenWidth;
	h = screenHeight;
	//printf("_____TEST_1_____\n");
  while(x++ < w)
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
		for (y = drawstart; y<drawend; y++)
		{
			texY = (int)texPos & (texHeight - 1);
			texPos += step;
			if (side == 1)
				texY = (int)texPos & (texHeight - 1);
			texPos += step;
			if (side == 1)
			{
				if (raydiry >= 0)
					mlx->color = RGB_Blue;
				else
					mlx->color = RGB_Green;
			}
			else
			{
				if (raydirx >= 0)
					mlx->color = RGB_Red;
				else
					mlx->color = RGB_Yellow;
			}
			//printf("x: %d, y : %d \n", x, y);
			mlx_pixel_put(mlx->mlx, mlx->window, x, y, mlx->color);
			//printf("%X\n", mlx->color);
		}
	
	  //draw the pixels of the stripe as a vertical line
	  //verLine(x, drawStart, drawEnd, color);
	//printf("_____TEST_9_____\n");

	//speed modifiers
	moveSpeed = 1.0; //the constant value is in squares/second
	rotSpeed = 3.0; //the constant value is in radians/second
	/*readKeys();
	//move forward if no wall in front of you
	if(keyDown(UP_KEY))
	{
	  if(worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == 0) posX += dirX * moveSpeed;
	  if(worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
	}
	//move backwards if no wall behind you
	if(keyDown(DOWN_KEY))
	{
	  if(worldMap[(int)(posX - dirX * moveSpeed)][(int)(posY)] == 0) posX -= dirX * moveSpeed;
	  if(worldMap[(int)(posX)][(int)(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
	}
	//rotate to the right
	if(keyDown(RIGHT_KEY))
	{
	  //both camera direction and camera plane must be rotated
		oldDirX = dirX;
	  dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
	  dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
	  double oldPlaneX = planeX;
	  planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
	  planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	//rotate to the left
	if(keyDown(LEFT_KEY))
	{
	  //both camera direction and camera plane must be rotated
	  oldDirX = dirX;
	  dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
	  dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
	  oldPlaneX = planeX;
	  planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
	  planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
	*/
  }
//printf("_____TEST_10_____\n");
//put_frame(mlx);
return (0);
}
void	player_init(t_mlx *mlx)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	player->posX = 22;
	player->posY = 12;
	player->dirX = -1;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0.86;
	mlx->player = player;

}
/*
void	put_image(t_mlx *mlx)
{
	int *dst;

	dst = mlx->data + (64 * 64 + 64 * (mlx->bpp / 8));
	*(unsigned int*)dst = mlx->color;
}
*/

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
	mlx->window = mlx_new_window(mlx->mlx, screenWidth, screenHeight, "Cub3D");
	mlx->frame = NULL;
	put_frame(mlx);
	raycasting(mlx);
	//mlx->mlx = mlx_new_image(mlx, screenHeight, screenWidth);
	//put_image(mlx);
	//mlx_hook(mlx->window, 2, 0, move, mlx);
	/*
	for (int x = 0; x < screenWidth; x++)
		for (int y = 0; y < screenHeight; y++)
			{
				//mlx->data[x + y * screenWidth] = 0xFF000000;
				mlx_pixel_put(mlx->mlx, mlx->window, x, y, 0x00FF0000);
			}
			*/
	//mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->frame, 0, 0);
	mlx_loop(mlx->mlx);
	return (0);
}
