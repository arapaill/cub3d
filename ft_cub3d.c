/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:48:38 by arapaill          #+#    #+#             */
/*   Updated: 2020/09/17 12:57:18 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
Copyright (c) 2004-2019, Lode Vandevenne
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
	* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "ft_cub3d.h"

/*
g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/

//place the example code below here:


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
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int raycasting(t_mlx *mlx)
{

	int w;
	int x = 0;
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
	int color;
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
	//double oldDirX;
	//double oldPlaneX;



	hit = 0;
	w = screenWidth;
	h = screenHeight;
	printf("_____TEST_1_____\n");
  while(x < w)
  {
	printf("_____TEST_2_____\n");
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
	printf("_____TEST_3_____\n");
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
	  printf("_____TEST_4_____\n");
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
	  printf("_____TEST_5_____\n");
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
		printf("_____TEST_6_____\n");
		//Check if ray has hit a wall
		if(worldMap[mapX][mapY] > '0') 
		if(worldMap[mapX][mapY] > 0) 
			hit = 1;		
	  }
	  //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
	  if(side == 0)
		perpWallDist = (mapX - mlx->player->posX + (1 - stepX) / 2) / rayDirX;
	  else
	 	perpWallDist = (mapY - mlx->player->posY + (1 - stepY) / 2) / rayDirY;

	  //Calculate height of line to draw on screen
	  h = mapHeight;
		lineHeight = (int)(h / perpWallDist);
printf("_____TEST_7_____\n");
	  //calculate lowest and highest pixel to fill in current stripe
	  drawStart = -lineHeight / 2 + h / 2;
	  if(drawStart < 0)
	  	drawStart = 0;
	  drawEnd = lineHeight / 2 + h / 2;
	  if(drawEnd >= h)
	  	drawEnd = h - 1;
printf("_____TEST_8_____\n");
	  //choose wall color
	  switch(worldMap[mapX][mapY])
	  {
		case 1:  color = RGB_Red;    break; //red
		case 2:  color = RGB_Green;  break; //green
		case 3:  color = RGB_Blue;   break; //blue
		case 4:  color = RGB_White;  break; //white
		default: color = RGB_Yellow; break; //yellow
	  }

	  //give x and y sides different brightness
	  if(side == 1) {color = color / 2;}

	  //draw the pixels of the stripe as a vertical line
	  //verLine(x, drawStart, drawEnd, color);
	printf("_____TEST_9_____\n");
	
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
	x++;
  }
printf("_____TEST_10_____\n");
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


int		main(int argc, char *argv[])
{
	t_mlx *mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	player_init(mlx);
	if (argc == 2)
		parsing(argv[1], mlx);
	else
		return (1);
	mlx->window = mlx_new_window(mlx->mlx, screenWidth, screenHeight, "Cub3D");
	mlx->frame = NULL;
	raycasting(mlx);
	//mlx_hook(mlx->window, 2, 0, move, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
