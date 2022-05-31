/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_parsing_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:13:24 by seseo             #+#    #+#             */
/*   Updated: 2022/05/12 16:23:43 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_default_size(t_vars *vars, int *case_size, int *z_size);
static void	set_default_color(t_map *map);
static void	set_one_point(t_vars *vars, int case_size);

void	set_case_size(t_vars *vars, int case_size, int z_size)
{
	int	y;
	int	x;

	if (case_size == 0 || z_size == 0)
		set_default_size(vars, &case_size, &z_size);
	y = 0;
	while (y < vars->map.size[0])
	{
		x = 0;
		while (x < vars->map.size[1])
		{
			vars->map.coord_origin[y][x].x *= case_size;
			vars->map.coord_origin[y][x].y *= case_size;
			vars->map.coord_origin[y][x].z *= z_size;
			if (vars->map.z_max < (int)vars->map.coord_origin[y][x].z)
				vars->map.z_max = (int)vars->map.coord_origin[y][x].z;
			x++;
		}
		y++;
	}
	set_default_color(&vars->map);
	set_one_point(vars, case_size);
	vars->map.f.c_flag = 1;
}

static void	set_default_size(t_vars *vars, int *case_size, int *z_size)
{
	int	l;
	int	scale;

	l = vars->size[0] / 2;
	if (vars->map.size[0] >= vars->map.size[1]
		&& vars->map.size[0] > vars->map.z_max)
		scale = l / vars->map.size[0];
	else if (vars->map.size[1] > vars->map.size[0]
		&& vars->map.size[1] > vars->map.z_max)
		scale = l / vars->map.size[1];
	else
		scale = l / (int)vars->map.z_max;
	*case_size = scale;
	*z_size = scale;
}

static void	set_one_point(t_vars *vars, int case_size)
{
	if (vars->map.size[0] * 3 > vars->map.size[1] * 3)
		vars->map.one_point = vars->map.size[0] * case_size * 3;
	else
		vars->map.one_point = vars->map.size[1] * case_size * 3;
	if (vars->map.z_max > vars->map.one_point)
		vars->map.one_point = vars->map.z_max * 3;
}

static void	set_default_color(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->size[0])
	{
		x = 0;
		while (x < map->size[1])
		{
			if (map->f.c_flag == 0
				&& (map->coord_origin[y][x].z > 0.7 * map->z_max))
				map->coord_origin[y][x].color
					= (int)(map->coord_origin[y][x].z
						/ map->z_max * 0xFF) << 16;
			x++;
		}
		y++;
	}
}

void	set_default_param(t_vars *vars)
{
	vars->map.angle.alpha = 0;
	vars->map.angle.beta = 0;
	vars->map.angle.gamma = 0;
	vars->map.f.p_flag = 0;
	vars->map.f.t_flag = 1;
	vars->map.x_axis[0] = 1;
	vars->map.x_axis[1] = 0;
	vars->map.x_axis[2] = 0;
	vars->map.y_axis[0] = 0;
	vars->map.y_axis[1] = 1;
	vars->map.y_axis[2] = 0;
	vars->map.z_axis[0] = 0;
	vars->map.z_axis[1] = 0;
	vars->map.z_axis[2] = 1;
	copy_coord(vars, vars->map.coord_origin, vars->map.coord_quat);
}
