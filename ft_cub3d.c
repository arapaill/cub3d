/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 10:18:59 by marvin            #+#    #+#             */
/*   Updated: 2020/06/17 14:46:00 by user42           ###   ########.fr       */
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

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24
#define RGB_Red 16711680
#define RGB_Green 65280
#define RGB_Blue 255
#define RGB_White 16777215
#define RGB_Yellow 16776960


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

int main()
{
	int w;
	int x;
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

	double time = 0; //time of current frame
  	double oldTime = 0; //time of previous frame
	
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double cameraX;
	double rayDirX;
	double rayDirY;
	//length of ray from current position to next x or y-side
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	double frameTime;
	double moveSpeed;
	double rotSpeed;
	double oldDirX;
	double oldPlaneX;

//x and y start position
	posX = 22;
	posY = 12;  
//initial direction vector
  	dirX = -1;
	dirY = 0; 
//the 2d raycaster version of camera plane
  	planeX = 0;
	planeY = 0.66;
	hit = 0;
	w = screenWidth;
	h = screenHeight;
  while(!done())
  {
	for(x = 0; x < w; x++)
	{
	//calculate ray position and direction
		cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		rayDirX = dirX + planeX * cameraX;
	  	rayDirY = dirY + planeY * cameraX;
	  //which box of the map we're in
	  mapX = (int)posX;
	  mapY = (int)posY;

	   //length of ray from one x or y-side to next x or y-side
	  deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
	  deltaDistY = (rayDirX== 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));

	  //what direction to step in x or y-direction (either +1 or -1)
	  //calculate step and initial sideDist
	  if(rayDirX < 0)
	  {
		stepX = -1;
		sideDistX = (posX - mapX) * deltaDistX;
	  }
	  else
	  {
		stepX = 1;
		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	  }
	  if(rayDirY < 0)
	  {
		stepY = -1;
		sideDistY = (posY - mapY) * deltaDistY;
	  }
	  else
	  {
		stepY = 1;
		sideDistY = (mapY + 1.0 - posY) * deltaDistY;
	  }
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
		//Check if ray has hit a wall
		if(worldMap[mapX][mapY] > 0) hit = 1;
	  }
	  //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
	  if(side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
	  else          perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

	  //Calculate height of line to draw on screen
		lineHeight = (int)(h / perpWallDist);

	  //calculate lowest and highest pixel to fill in current stripe
	  drawStart = -lineHeight / 2 + h / 2;
	  if(drawStart < 0)drawStart = 0;
	  drawEnd = lineHeight / 2 + h / 2;
	  if(drawEnd >= h)drawEnd = h - 1;

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
	  verLine(x, drawStart, drawEnd, color);
	}
	//timing for input and FPS counter
	oldTime = time;
	time = getTicks();
	frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
	print(1.0 / frameTime); //FPS counter
	redraw();
	cls();

	//speed modifiers
	moveSpeed = frameTime * 5.0; //the constant value is in squares/second
	rotSpeed = frameTime * 3.0; //the constant value is in radians/second
	readKeys();
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
  }
}
