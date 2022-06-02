/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:19:30 by seseo             #+#    #+#             */
/*   Updated: 2022/05/10 21:00:32 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	copy_coord(t_vars *vars, t_point **coord1, t_point **coord2)
{
	int		x;
	int		y;

	y = 0;
	while (y < vars->map.size[0])
	{
		x = 0;
		while (x < vars->map.size[1])
		{
			coord2[y][x].x = coord1[y][x].x;
			coord2[y][x].y = coord1[y][x].y;
			coord2[y][x].z = coord1[y][x].z;
			coord2[y][x].color = coord1[y][x].color;
			x++;
		}
		y++;
	}
}

void	free_map(t_map *map)
{
	int	y;

	y = 0;
	while (y < map->size[0])
	{
		free(map->coord_origin[y]);
		free(map->coord_quat[y]);
		free(map->coord[y]);
		y++;
	}
	free(map->coord_origin);
	free(map->coord_quat);
	free(map->coord);
}

void	object_zooming(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->size[0])
	{
		x = 0;
		while (x < map->size[1])
		{
			map->coord[y][x].x *= map->s;
			map->coord[y][x].y *= map->s;
			map->coord[y][x].z *= map->s;
			x++;
		}
		y++;
	}
}

int	change_scale(int keycode, int x, int y, t_vars *vars)
{
	x++;
	y++;
	if (keycode == 4)
		vars->map.s += 0.2;
	else if (keycode == 5)
	{
		if (vars->map.s > 0.21)
			vars->map.s -= 0.2;
	}
	return (0);
}
