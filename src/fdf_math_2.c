/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_math_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:07:34 by seseo             #+#    #+#             */
/*   Updated: 2022/05/11 17:29:17 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cal_rot_mtx(t_map *map)
{
	const double	a = M_PI_4 / 3 * map->angle.alpha;
	const double	b = M_PI_4 / 3 * map->angle.beta;
	const double	g = M_PI_4 / 3 * map->angle.gamma;

	map->rot_mtx[0][0] = cos(a) * cos(b);
	map->rot_mtx[0][1] = cos(a) * sin(b) * sin(g) - sin(a) * cos(g);
	map->rot_mtx[0][2] = cos(a) * sin(b) * cos(g) + sin(a) * sin(g);
	map->rot_mtx[1][0] = sin(a) * cos(b);
	map->rot_mtx[1][1] = sin(a) * sin(b) * sin(g) + cos(a) * cos(g);
	map->rot_mtx[1][2] = sin(a) * sin(b) * cos(g) - cos(a) * sin(g);
	map->rot_mtx[2][0] = -sin(b);
	map->rot_mtx[2][1] = cos(b) * sin(g);
	map->rot_mtx[2][2] = cos(b) * cos(g);
}

void	rotate_vec(t_map *map, int x, int y)
{
	double	x_new;
	double	y_new;
	double	z_new;

	x_new = map->rot_mtx[0][0] * map->coord[y][x].x
		+ map->rot_mtx[0][1] * map->coord[y][x].y
		+ map->rot_mtx[0][2] * map->coord[y][x].z;
	y_new = map->rot_mtx[1][0] * map->coord[y][x].x
		+ map->rot_mtx[1][1] * map->coord[y][x].y
		+ map->rot_mtx[1][2] * map->coord[y][x].z;
	z_new = map->rot_mtx[2][0] * map->coord[y][x].x
		+ map->rot_mtx[2][1] * map->coord[y][x].y
		+ map->rot_mtx[2][2] * map->coord[y][x].z;
	map->coord[y][x].x = x_new;
	map->coord[y][x].y = y_new;
	map->coord[y][x].z = z_new;
}

void	get_rot_quat(t_vars *vars, double rot_v[3], double angle)
{
	double	abcd[4];

	abcd[0] = cos(angle / 2);
	abcd[1] = sin(angle / 2) * rot_v[0];
	abcd[2] = sin(angle / 2) * rot_v[1];
	abcd[3] = sin(angle / 2) * rot_v[2];
	vars->map.rot_quat[0][0] = abcd[0] * abcd[0] + abcd[1] * abcd[1]
		- abcd[2] * abcd[2] - abcd[3] * abcd[3];
	vars->map.rot_quat[0][1] = 2 * (abcd[1] * abcd[2] - abcd[0] * abcd[3]);
	vars->map.rot_quat[0][2] = 2 * (abcd[1] * abcd[3] + abcd[0] * abcd[2]);
	vars->map.rot_quat[1][0] = 2 * (abcd[1] * abcd[2] + abcd[0] * abcd[3]);
	vars->map.rot_quat[1][1] = abcd[0] * abcd[0] - abcd[1] * abcd[1]
		+ abcd[2] * abcd[2] - abcd[3] * abcd[3];
	vars->map.rot_quat[1][2] = 2 * (abcd[2] * abcd[3] - abcd[0] * abcd[1]);
	vars->map.rot_quat[2][0] = 2 * (abcd[1] * abcd[3] - abcd[0] * abcd[2]);
	vars->map.rot_quat[2][1] = 2 * (abcd[2] * abcd[3] + abcd[0] * abcd[1]);
	vars->map.rot_quat[2][2] = abcd[0] * abcd[0] - abcd[1] * abcd[1]
		- abcd[2] * abcd[2] + abcd[3] * abcd[3];
}

void	rotate_vector_quat(double vec[3], double rot_quat[3][3])
{
	double	fgh[3];

	fgh[0] = rot_quat[0][0] * vec[0] + rot_quat[0][1] * vec[1]
		+ rot_quat[0][2] * vec[2];
	fgh[1] = rot_quat[1][0] * vec[0] + rot_quat[1][1] * vec[1]
		+ rot_quat[1][2] * vec[2];
	fgh[2] = rot_quat[2][0] * vec[0] + rot_quat[2][1] * vec[1]
		+ rot_quat[2][2] * vec[2];
	vec[0] = fgh[0];
	vec[1] = fgh[1];
	vec[2] = fgh[2];
}
