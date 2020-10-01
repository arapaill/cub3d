/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:52:34 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/01 16:17:12 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include <math.h>
# include <mlx.h>
# include "keynote.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

# define RGB_Red 16711680
# define RGB_Green 65280
# define RGB_Blue 255
# define RGB_White 16777215
# define RGB_Yellow 16776960

# define mapWidth 34
# define mapHeight 25
# define texWidth 64
# define texHeight 64
# define movespeed 0.5
# define rotspeed 0.1

typedef struct  s_texture
{
    int         *south;
    int         *north;
    int         *east;
    int         *west;
    int         *floor;
    int         *ceiling;
    int         RGB_floor;
    int         RGB_ceiling;
}               t_texture;

typedef struct  s_player
{
    double      posX;
    double      posY;
    double      dirX;
    double      dirY;
    double      planeX;
    double      planeY;

}               t_player;
typedef struct  s_mlx
{
    void        *mlx;
    void        *window;
    int         screen_width;
    int         screen_height;
    char        **map;
    int         map_width;
    int         map_height;
    void        *frame;
    int        *data;
    int         bpp;
    int         sl;
    int         endian;
    int         color;
    t_player    *player;
    t_texture   *texture;
}               t_mlx;

void    parsing(char *file, t_mlx *mlx);
int		key_check( int key, t_mlx *mlx);
void	rot_right(t_mlx *mlx, double rot_speed);
void	rot_left(t_mlx *mlx, double rot_speed);
int     raycasting(t_mlx *mlx);
void	floor_ceiling(t_mlx *mlx);
#endif