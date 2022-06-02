/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:19:25 by seseo             #+#    #+#             */
/*   Updated: 2022/05/12 16:53:41 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_info(void *mlx, void *win, int c);
static void	rotated_coord_copy(t_vars *vars);

int	draw_loop(t_vars *vars)
{
	int	wh[2];

	vars->img.img = mlx_xpm_file_to_image(vars->mlx, "xpm/bg.xpm", wh, &wh[1]);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	rotated_coord_copy(vars);
	object_zooming(&vars->map);
	draw_lines(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	put_info(vars->mlx, vars->win, 0xFFFFFFFF);
	mlx_destroy_image(vars->mlx, vars->img.img);
	return (0);
}

static void	rotated_coord_copy(t_vars *vars)
{
	if (vars->map.f.t_flag)
	{
		copy_coord(vars, vars->map.coord_origin, vars->map.coord);
		apply_one_point(&vars->map);
		do_rotate(&vars->map);
		return ;
	}
	if (vars->map.angle.alpha || vars->map.angle.beta || vars->map.angle.gamma)
	{
		if (vars->map.angle.alpha)
			get_rot_quat(vars, vars->map.z_axis,
				((double)vars->map.angle.alpha) * M_PI_4 / 3);
		else if (vars->map.angle.beta)
			get_rot_quat(vars, vars->map.y_axis,
				((double)vars->map.angle.beta) * M_PI_4 / 3);
		else if (vars->map.angle.gamma)
			get_rot_quat(vars, vars->map.x_axis,
				((double)vars->map.angle.gamma) * M_PI_4 / 3);
		vars->map.angle.alpha = 0;
		vars->map.angle.beta = 0;
		vars->map.angle.gamma = 0;
		do_rotate_quat(&vars->map);
	}
	copy_coord(vars, vars->map.coord_quat, vars->map.coord);
}

static void	put_info(void *mlx, void *win, int c)
{
	mlx_string_put(mlx, win, 50, 50, 0xFF << 16, "** Rotate **");
	mlx_string_put(mlx, win, 50, 80, 0xFF << 8, "o : quaternion on / off");
	mlx_string_put(mlx, win, 50, 100, c, "q / w : z axis rotate");
	mlx_string_put(mlx, win, 50, 120, c, "a / s : y axis rotate");
	mlx_string_put(mlx, win, 50, 140, c, "z / x : x axis rotate");
	mlx_string_put(mlx, win, 50, 190, 0xFF << 16, "** Projection **");
	mlx_string_put(mlx, win, 50, 220, c, "i : isometric view");
	mlx_string_put(mlx, win, 50, 240, c, "p : perspective view on / off");
	mlx_string_put(mlx, win, 50, 290, 0xFF << 16, "** Zoom **");
	mlx_string_put(mlx, win, 50, 320, c, "scroll up : zoom in");
	mlx_string_put(mlx, win, 50, 340, c, "scroll down : zoom out");
	mlx_string_put(mlx, win, 50, 390, 0xFF << 16, "** Translate **");
	mlx_string_put(mlx, win, 50, 420, c, "press arrow keys to translate");
	mlx_string_put(mlx, win, 940, 50, 0xFF << 16, "** Color **");
	mlx_string_put(mlx, win, 940, 80, c, "c : color on / off");
	mlx_string_put(mlx, win, 940, 130, 0xFF << 16, "** Reset **");
	mlx_string_put(mlx, win, 940, 160, c, "r : reset all params");
}
