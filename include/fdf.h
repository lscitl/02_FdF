/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:53:15 by seseo             #+#    #+#             */
/*   Updated: 2022/05/12 16:59:23 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/include/libft.h"
# include <math.h>
# include <fcntl.h>
# include <mlx.h>

# define _USE_MATH_DEFINES

# define TRUE 1
# define FALSE 0

# define KEY_Q 12
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_R 15
# define KEY_O 31
# define KEY_I 34
# define KEY_P 35
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53
# define KEY_EVENT_PRESS 2
# define KEY_EVENT_EXIT 17

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_angle
{
	int		alpha;
	int		beta;
	int		gamma;
}	t_angle;

typedef struct s_trans
{
	double	t_x;
	double	t_y;
}	t_trans;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		color;
}	t_point;

typedef struct s_flag
{
	int		t_flag;
	int		p_flag;
	int		c_flag;
}	t_flag;

// size[0]: y_size, size[1]: x_size
typedef struct s_map
{
	t_point		**coord_origin;
	t_point		**coord_quat;
	t_point		**coord;
	t_angle		angle;
	t_trans		t;
	t_flag		f;
	int			size[2];
	double		s;
	double		rot_mtx[3][3];
	double		rot_quat[3][3];
	double		one_point;
	double		z_axis[3];
	double		y_axis[3];
	double		x_axis[3];
	int			z_max;
}	t_map;

// size[0]: x_size, size[1]: y_size
typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_data	img;
	int		size[2];
}	t_vars;

// fdf_map_parsing_1.c
void	map_parsing(char *file_name, t_vars *vars, int case_size, int z_size);

// fdf_map_parsing_2.c
void	set_coord(t_map *map, char *file_name);

// fdf_map_parsing_3.c
void	set_default_param(t_vars *vars);
void	set_case_size(t_vars *vars, int case_size, int z_size);
void	print_coord(t_map *map, t_point **coord);

// fdf_draw_line.c
void	draw_lines(t_vars *vars);

// fdf_utils.c
void	copy_coord(t_vars *vars, t_point **coord1, t_point **coord2);
void	free_map(t_map *map);
int		change_scale(int keycode, int x, int y, t_vars *vars);
void	object_zooming(t_map *map);

// fdf_projection_utils.c
void	apply_one_point(t_map *map);
void	iso_view(t_vars *vars);
void	do_rotate(t_map *map);
void	do_rotate_quat(t_map *map);

// fdf_key_hook.c
int		key_hook(int keycode, t_vars *vars);
int		exit_hook(t_vars *vars);

// fdf_mlx_loop.c
int		draw_loop(t_vars *vars);

// fdf_math_1.c
void	cross_product(double a[3], double b[3], double result[3]);
double	dot_product(double a[3], double b[3]);
double	vector_size(double a[3]);
void	make_unit_vector(double a[3]);
double	get_angle(double a[3], double b[3]);

// fdf_math_2.c
void	rotate_vec(t_map *map, int x, int y);
void	cal_rot_mtx(t_map *map);
void	get_rot_quat(t_vars *vars, double rot_v[3], double angle);
void	rotate_vector_quat(double vec[3], double rot_quat[3][3]);

#endif
