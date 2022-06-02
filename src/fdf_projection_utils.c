/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_projection_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:25:42 by seseo             #+#    #+#             */
/*   Updated: 2022/05/12 16:59:05 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_one_point(t_map *map)
{
	int		x;
	int		y;

	if (map->f.p_flag == 0)
		return ;
	y = 0;
	while (y < map->size[0])
	{
		x = 0;
		while (x < map->size[1])
		{
			map->coord[y][x].x
				*= 1 - map->coord[y][x].z / map->one_point;
			map->coord[y][x].y
				*= 1 - map->coord[y][x].z / map->one_point;
			x++;
		}
		y++;
	}
}

void	iso_view(t_vars *vars)
{
	double	iso[3];
	double	rot_axis[3];
	double	angle;

	if (vars->map.f.t_flag == 1)
	{
		vars->map.angle.alpha = -2;
		vars->map.angle.beta = 2;
		vars->map.angle.gamma = 3;
		return ;
	}
	iso[0] = -1;
	iso[1] = -1;
	iso[2] = 1;
	vars->map.angle.alpha = 0;
	vars->map.angle.beta = 0;
	vars->map.angle.gamma = 0;
	make_unit_vector(iso);
	cross_product(vars->map.z_axis, iso, rot_axis);
	angle = get_angle(vars->map.z_axis, iso);
	get_rot_quat(vars, rot_axis, angle);
	do_rotate_quat(&vars->map);
}

void	do_rotate(t_map *map)
{
	int	y;
	int	x;

	cal_rot_mtx(map);
	y = 0;
	while (y < map->size[0])
	{
		x = 0;
		while (x < map->size[1])
		{
			rotate_vec(map, x, y);
			x++;
		}
		y++;
	}
}

void	do_rotate_quat(t_map *map)
{
	double	vec[3];
	int		y;
	int		x;

	y = 0;
	while (y < map->size[0])
	{
		x = 0;
		while (x < map->size[1])
		{
			vec[0] = map->coord_quat[y][x].x;
			vec[1] = map->coord_quat[y][x].y;
			vec[2] = map->coord_quat[y][x].z;
			rotate_vector_quat(vec, map->rot_quat);
			map->coord_quat[y][x].x = vec[0];
			map->coord_quat[y][x].y = vec[1];
			map->coord_quat[y][x].z = vec[2];
			x++;
		}
		y++;
	}
	rotate_vector_quat(map->x_axis, map->rot_quat);
	rotate_vector_quat(map->y_axis, map->rot_quat);
	rotate_vector_quat(map->z_axis, map->rot_quat);
}
