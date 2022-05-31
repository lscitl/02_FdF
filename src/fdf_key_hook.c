/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:20:52 by seseo             #+#    #+#             */
/*   Updated: 2022/05/12 17:01:39 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_angle(t_vars *vars, int keycode);
static void	arrow_command(t_vars *vars, int keycode);

// key press event hook
int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		exit_hook(vars);
	else if (keycode == KEY_Q || keycode == KEY_W || keycode == KEY_A
		|| keycode == KEY_S || keycode == KEY_Z || keycode == KEY_X)
		set_angle(vars, keycode);
	else if (keycode == KEY_P)
		vars->map.f.p_flag = !vars->map.f.p_flag;
	else if (keycode == KEY_C)
		vars->map.f.c_flag = !vars->map.f.c_flag;
	else if (keycode == KEY_I)
		iso_view(vars);
	else if (keycode == KEY_R)
		set_default_param(vars);
	else if (keycode == KEY_O)
		vars->map.f.t_flag = !vars->map.f.t_flag;
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT
		|| keycode == KEY_UP || keycode == KEY_DOWN)
		arrow_command(vars, keycode);
	return (0);
}

static void	arrow_command(t_vars *vars, int keycode)
{
	if (keycode == KEY_LEFT)
		vars->map.t.t_x -= 20;
	else if (keycode == KEY_RIGHT)
		vars->map.t.t_x += 20;
	else if (keycode == KEY_UP)
		vars->map.t.t_y -= 20;
	else if (keycode == KEY_DOWN)
		vars->map.t.t_y += 20;
}

static void	set_angle(t_vars *vars, int keycode)
{
	if (keycode == KEY_Q)
		vars->map.angle.alpha += 1;
	else if (keycode == KEY_W)
		vars->map.angle.alpha -= 1;
	else if (keycode == KEY_A)
		vars->map.angle.beta += 1;
	else if (keycode == KEY_S)
		vars->map.angle.beta -= 1;
	else if (keycode == KEY_Z)
		vars->map.angle.gamma += 1;
	else if (keycode == KEY_X)
		vars->map.angle.gamma -= 1;
}

// close button press event
int	exit_hook(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	free_map(&vars->map);
	exit(0);
}
