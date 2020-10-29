/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:52:34 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/29 12:29:01 by arapaill         ###   ########.fr       */
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
# define MOVESPEED 0.3
# define IMG_DEPTH 3
# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40
# define FILENAME "capture.bmp"

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

typedef struct	s_float
{
	float		x;
	float		y;
}				t_float;

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

typedef struct	s_ray
{
	int			w;
	int			h;
	int			x;
	int			y;
	int			hit;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			side;
	t_point		map;
	t_point		d_step;
	t_point		tex;
	double		camerax;
	double		perpwalldist;
	double		wallx;
	double		step;
	double		texpos;
	t_double	raydir;
	t_double	sidedist;
	t_double	deltadist;

}				t_ray;

typedef struct	s_fnc
{
	t_float		raydira;
	t_float		raydirb;
	t_float		floorstep;
	t_float		floor;
	t_float		cell;
	t_point		t;
	float		posz;
	float		rowdistance;
	int			color;
}				t_fnc;

typedef struct	s_map_pars
{
	char		*line;
	char		**world_map;
	int			fd;
	int			ret;
}				t_pars;

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
	int			capture;
	t_ray		*ray;
	t_fnc		*fnc;
	t_pars		*pars;
}				t_mlx;

int				key_check(int key, t_mlx *mlx);
void			rot_right(t_mlx *mlx, double rot_speed);
void			rot_left(t_mlx *mlx, double rot_speed);
void			floor_ceiling(t_mlx *mlx);
int				map_check(t_mlx *mlx);
int				freemap(char **map, int n, t_mlx *mlx);
void			error_manager(int error, t_mlx *mlx);
void			serpilliere(t_mlx *mlx);
void			bmp_capture(t_mlx *mlx);
void			put_frame(t_mlx *mlx);
void			check_name(t_mlx *mlx, char *s);
void			map_separete(t_mlx *mlx, char *file);
void			init_data_mlx(t_mlx *mlx);

/*
**	raycasting
*/

void			pre_hit(t_mlx *mlx, t_ray *ray);
void			hit(t_mlx *mlx, t_ray *ray);
int				raycasting(t_mlx *mlx);

/*
**	sprite
*/

void			ordersprites(t_sort *sprite, int amount, double *dist);
void			sortsprite(int *order, double *dist, int amount, t_mlx *mlx);
void			parsing_sprite(t_mlx *mlx, t_sprite *sprite);
void			add_sprites(t_mlx *mlx);

/*
** Parsing
*/

void			parsing(char *file, t_mlx *mlx);
char			**creat_world_map(char *file, t_mlx *mlx);
void			id_check(t_mlx *mlx, char *line, int fd);
int				fc_atoi(char *s, t_mlx *mlx);
void			height_width(char *s, t_mlx *mlx);
void			get_texture(char *s, t_mlx *mlx);
int				gnl(char *line, int fd, int w, t_mlx *mlx);
void			text_fc(char *s, t_mlx *mlx, void *texture);
void			text_snwebr(char *s, t_mlx *mlx, void *texture);
void			size_file(t_mlx *mlx, char *file);
int				no_double(t_mlx *mlx, char c);
#endif
