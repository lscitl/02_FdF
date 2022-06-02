/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:34:30 by seseo             #+#    #+#             */
/*   Updated: 2022/05/12 14:12:32 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_win(t_vars *vars, char *file_name, int case_size, int z_size);

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (argc != 2 && argc != 4)
	{
		ft_putendl_fd("Usage : ./fdf <filename> [ case_size z_size ]", 1);
		exit (1);
	}
	if (argc == 2)
		init_win(&vars, argv[1], 0, 0);
	else
		init_win(&vars, argv[1], ft_atoi(argv[2]), ft_atoi(argv[3]));
	mlx_mouse_hook(vars.win, &change_scale, &vars);
	mlx_key_hook(vars.win, &key_hook, &vars);
	mlx_hook(vars.win, KEY_EVENT_EXIT, 0, &exit_hook, &vars);
	mlx_loop_hook(vars.mlx, draw_loop, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

static void	init_win(t_vars *vars, char *file_name, int case_size, int z_size)
{
	vars->mlx = mlx_init();
	vars->size[0] = 1200;
	vars->size[1] = 800;
	vars->win = mlx_new_window(vars->mlx, vars->size[0], vars->size[1], "fdf");
	map_parsing(file_name, vars, case_size, z_size);
	vars->map.t.t_x = vars->size[0] / 2;
	vars->map.t.t_y = vars->size[1] / 2;
	vars->map.s = 1;
}
