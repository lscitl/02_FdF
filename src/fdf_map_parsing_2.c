/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_parsing_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:13:24 by seseo             #+#    #+#             */
/*   Updated: 2022/05/12 13:34:46 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	malloc_coord(t_map *map);
static void	set_coord_sub(t_map *map, char *str, int y);
static void	set_coord_sub2(t_map *map, char **points, int x, int y);

void	set_coord(t_map *map, char *file_name)
{
	char	*str;
	int		y;
	int		fd;

	malloc_coord(map);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	map->f.c_flag = 0;
	y = 0;
	while (TRUE)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		set_coord_sub(map, str, y);
		y++;
	}
	close(fd);
}

static void	malloc_coord(t_map *map)
{
	map->coord_origin = malloc(sizeof(t_point *) * (map->size[0] + 1));
	map->coord_quat = malloc(sizeof(t_point *) * (map->size[0] + 1));
	map->coord = malloc(sizeof(t_point *) * (map->size[0] + 1));
	if (map->coord_origin == NULL || map->coord == NULL
		|| map->coord_quat == NULL)
		exit(EXIT_FAILURE);
	map->coord_origin[map->size[0]] = NULL;
	map->coord_quat[map->size[0]] = NULL;
	map->coord[map->size[0]] = NULL;
}

static void	set_coord_sub(t_map *map, char *str, int y)
{
	char	**points;
	int		x;

	points = ft_split(str, ' ');
	if (points == NULL)
		exit(EXIT_FAILURE);
	free(str);
	map->coord_origin[y] = ft_calloc(sizeof(t_point), map->size[1]);
	map->coord_quat[y] = ft_calloc(sizeof(t_point), map->size[1]);
	map->coord[y] = ft_calloc(sizeof(t_point), map->size[1]);
	if (map->coord_origin[y] == NULL || map->coord[y] == NULL
		|| map->coord_quat[y] == NULL)
		exit(EXIT_FAILURE);
	x = 0;
	while (points[x])
	{
		set_coord_sub2(map, points, x, y);
		free(points[x]);
		x++;
	}
	free(points);
}

static void	set_coord_sub2(t_map *map, char **points, int x, int y)
{
	char	**p_info;

	if (x < map->size[1])
	{
		map->coord_origin[y][x].x = (double)x - (map->size[1] - 1) / 2;
		map->coord_origin[y][x].y = (double)y - (map->size[0] - 1) / 2;
		if (ft_strchr(points[x], ',') != NULL)
		{
			map->f.c_flag = 1;
			p_info = ft_split(points[x], ',');
			if (p_info == NULL)
				exit(1);
			map->coord_origin[y][x].z = (double)ft_atoi(p_info[0]);
			map->coord_origin[y][x].color = ft_hextoi(p_info[1]);
			free(p_info[0]);
			free(p_info[1]);
			free(p_info);
		}
		else
		{
			map->coord_origin[y][x].z = (double)ft_atoi(points[x]);
			map->coord_origin[y][x].color = 0x00FFFFFF;
		}
	}
}
