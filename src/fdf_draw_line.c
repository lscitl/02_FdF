/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:35:18 by seseo             #+#    #+#             */
/*   Updated: 2022/05/12 15:17:34 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line(t_vars *vars, int x, int y, char direction);
static void	draw_line_sub(double p1[2], double p2[2], int c[2], t_vars *vars);
static void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
static int	get_color(int c[2], double i, double len);

void	draw_lines(t_vars *vars)
{
	int	y;
	int	x;

	y = 0;
	while (y < vars->map.size[0])
	{
		x = 0;
		while (x < vars->map.size[1])
		{
			if (x != vars->map.size[1] - 1 && y != vars->map.size[0] - 1)
			{
				draw_line(vars, x, y, 'd');
				draw_line(vars, x, y, 'r');
			}
			else if (x == vars->map.size[1] - 1 && y != vars->map.size[0] - 1)
				draw_line(vars, x, y, 'd');
			else if (x != vars->map.size[1] - 1 && y == vars->map.size[0] - 1)
				draw_line(vars, x, y, 'r');
			x++;
		}
		y++;
	}
}

static void	draw_line(t_vars *vars, int x, int y, char direction)
{
	double	p1[2];
	double	p2[2];
	int		c[2];

	p1[0] = vars->map.coord[y][x].x + vars->map.t.t_x;
	p1[1] = vars->map.coord[y][x].y + vars->map.t.t_y;
	c[0] = vars->map.coord[y][x].color;
	if (direction == 'd')
	{
		p2[0] = vars->map.coord[y + 1][x].x + vars->map.t.t_x;
		p2[1] = vars->map.coord[y + 1][x].y + vars->map.t.t_y;
		c[1] = vars->map.coord[y + 1][x].color;
	}
	else if (direction == 'r')
	{
		p2[0] = vars->map.coord[y][x + 1].x + vars->map.t.t_x;
		p2[1] = vars->map.coord[y][x + 1].y + vars->map.t.t_y;
		c[1] = vars->map.coord[y][x + 1].color;
	}
	else
		exit(1);
	draw_line_sub(p1, p2, c, vars);
}

static void	draw_line_sub(double p1[2], double p2[2], int c[2], t_vars *vars)
{
	double	len;
	double	i;
	double	p[2];
	int		color;

	len = fabs(p2[0] - p1[0]);
	if (fabs(p2[1] - p1[1]) > len)
		len = fabs(p2[1] - p1[1]);
	color = 0;
	i = 0;
	while (i <= len)
	{
		p[0] = p1[0] + i / len * (p2[0] - p1[0]) - 0.1;
		p[1] = p1[1] + i / len * (p2[1] - p1[1]) - 0.1;
		color = 0xFFFFFF;
		if (vars->map.f.c_flag)
			color = get_color(c, i, len);
		if (p[0] >= 0 && p[0] <= vars->size[0]
			&& p[1] >= 0 && p[1] <= vars->size[1])
			my_mlx_pixel_put(&vars->img, p[0], p[1], color);
		i++;
	}
}

static int	get_color(int c[2], double i, double len)
{
	int	color[4];
	int	j;

	j = 0;
	while (j < 4)
	{
		if ((c[0] & (0xFF << 8 * j)) < (c[1] & (0xFF << 8 * j)))
		{
			color[j] = ((c[0] & (0xFF << 8 * j)) >> 8 * j)
				| (int)(i / len * (((c[1] & (0xFF << 8 * j))
							^ (c[0] & (0xFF << 8 * j))) >> 8 * j) - 0.1);
		}
		else
		{
			color[j] = ((c[1] & (0xFF << 8 * j)) >> 8 * j)
				| (int)((len - i) / len * (((c[0] & (0xFF << 8 * j))
							^ (c[1] & (0xFF << 8 * j))) >> 8 * j) - 0.1);
		}
		j++;
	}
	return (color[3] << 24 | color[2] << 16 | color[1] << 8 | color[0]);
}

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
