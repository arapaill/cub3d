/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:52:34 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/09 16:04:10 by arapaill         ###   ########.fr       */
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
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define MOVESPEED 0.5

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_double
{
	double		x;
	double		y;
}				t_double;

typedef struct	s_sort
{
	double		first;
	int			second;
}				t_sort;

typedef struct	s_texture
{
	int			*south;
	int			*north;
	int			*east;
	int			*west;
	int			*floor;
	int			*ceiling;
	int			*sprite;
	int			rgb_floor;
	int			rgb_ceiling;
}				t_texture;

typedef struct	s_sprite
{
	int			*spriteorder;
	double		*spritedist;
	t_double	d_sprite;
	t_double	*p_sprite;
	double		invdet;
	t_double	transform;
	int			spritescreenx;
	int			sprite_height;
	int			sprite_width;
	int			color;
	t_point		draw_start;
	t_point		draw_end;
	t_point		tex;
	int			stripe;
}				t_sprite;

typedef struct	s_player
{
	t_double	pos;
	t_double	dir;
	t_double	plane;
	t_double	spawn;
}				t_player;

typedef struct	s_mlx
{
	void		*mlx;
	void		*window;
	int			screen_width;
	int			screen_height;
	char		**map;
	int			map_width;
	int			map_height;
	void		*frame;
	int			*data;
	int			bpp;
	int			sl;
	int			endian;
	int			color;
	double		*zbuffer;
	t_player	*player;
	t_texture	*texture;
	int			spritenbr;
	t_sprite	*sprite;
}				t_mlx;

void			parsing(char *file, t_mlx *mlx);
int				key_check(int key, t_mlx *mlx);
void			rot_right(t_mlx *mlx, double rot_speed);
void			rot_left(t_mlx *mlx, double rot_speed);
int				raycasting(t_mlx *mlx);
void			floor_ceiling(t_mlx *mlx);
int				map_check(t_mlx *mlx);
int				freemap(char **map, int n, t_mlx *mlx);
void			error_manager(int error, t_mlx *mlx);
void			serpilliere(t_mlx *mlx);
void			parsing_sprite(t_mlx *mlx, t_sprite *sprite);
void			add_sprites(t_mlx *mlx);
#endif
