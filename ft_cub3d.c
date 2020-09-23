/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:48:38 by arapaill          #+#    #+#             */
/*   Updated: 2020/09/23 16:58:05 by arapaill         ###   ########.fr       */
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
	int mapX;
	int mapY;
	int stepX;
	int stepY;
	int hit;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
	double cameraX;
	double rayDirX;
	double rayDirY;
	//length of ray from current position to next x or y-side
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
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
	//printf("_____TEST_2_____\n");
	//calculate ray position and direction
		cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		rayDirX = mlx->player->dirX + mlx->player->planeX * cameraX;
	  	rayDirY = mlx->player->dirY + mlx->player->planeY * cameraX;

	  //which box of the map we're in
	  mapX = (int)mlx->player->posX;
	  mapY = (int)mlx->player->posY;

	   //length of ray from one x or y-side to next x or y-side
	  deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
	  deltaDistY = (rayDirX== 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
	//printf("_____TEST_3_____\n");
	  //what direction to step in x or y-direction (either +1 or -1)
	  //calculate step and initial sideDist
	  if(rayDirX < 0)
	  {
		stepX = -1;
		sideDistX = (mlx->player->posX - mapX) * deltaDistX;
	  }
	  else
	  {
		stepX = 1;
		sideDistX = (mapX + 1.0 - mlx->player->posX) * deltaDistX;
	  }
	  //printf("_____TEST_4_____\n");
	  if(rayDirY < 0)
	  {
		stepY = -1;
		sideDistY = (mlx->player->posY - mapY) * deltaDistY;
	  }
	  else
	  {
		stepY = 1;
		sideDistY = (mapY + 1.0 - mlx->player->posY) * deltaDistY;
	  }
	  //printf("_____TEST_5_____\n");
	  //perform DDA
	  while (hit == 0)
	  {
		//jump to next map square, OR in x-direction, OR in y-direction
		if(sideDistX < sideDistY)
		{
		  sideDistX += deltaDistX;
		  mapX += stepX;
		  side = 0;
		}
		else
		{
		  sideDistY += deltaDistY;
		  mapY += stepY;
		  side = 1;
		}
		//printf("_____TEST_6_____\n");
		//Check if ray has hit a wall
		if(mlx->map[(int)mapX][(int)mapY] > '0') 
			hit = 1;		
	  }
	  //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
	  if(side == 0)
		perpWallDist = (mapX - mlx->player->posX + (1 - stepX) / 2) / rayDirX;
	  else
	 	perpWallDist = (mapY - mlx->player->posY + (1 - stepY) / 2) / rayDirY;
			//	printf("stepY : %d, stepX : %d \n", stepY, stepX);
	  //Calculate height of line to draw on screen
		lineHeight = (int)(h / perpWallDist);
		//printf("h: %d\n", h);
//printf("_____TEST_7_____\n");
	  //calculate lowest and highest pixel to fill in current stripe
      drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0)
	  	drawStart = 0;
    	drawEnd = lineHeight / 2 + h / 2;
		//printf("drawEnd : %d \n", lineHeight);
      if(drawEnd >= h)drawEnd = h - 1;
//printf("_____TEST_8_____\n");
	  //give x and y sides different brightness
	  if(side == 1) {mlx->color = mlx->color / 2;}
	  if (side == 0)
			wallX = mlx->player->posY + perpWallDist * rayDirY;
		else
			wallX = mlx->player->posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		step = 1.0 * texHeight / lineHeight;
		texPos = (drawStart - h / 2 + lineHeight / 2) * step;
		//printf("ds : %d, de : %d \n", drawStart, drawEnd);
		for (y = drawStart; y < drawEnd; y++)
		{
			texY = (int)texPos & (texHeight - 1);
			texPos += step;
			if (side == 1)
			{
				if (rayDirY >= 0)
					mlx->color = RGB_Blue;
				else
					mlx->color = RGB_Green;
			}
			else
			{
				if (rayDirX >= 0)
					mlx->color = RGB_Red;
				else
					mlx->color = RGB_Yellow;
			}
						printf("x: %d, y : %d \n", x, y);
			mlx_pixel_put(mlx->mlx, mlx->window, x, y, 0x00FF0000);
			printf("%X\n", mlx->color);
		}
			printf("x: %d, y : %d \n", x, y);
			mlx_pixel_put(mlx->mlx, mlx->window, x, y, 0x00FF0000);
			printf("%X\n", mlx->color);
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
	player->planeY = 0.66;
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
