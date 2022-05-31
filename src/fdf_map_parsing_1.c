/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_parsing_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:13:24 by seseo             #+#    #+#             */
/*   Updated: 2022/05/12 16:59:48 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_col_len(char *file_name, int size[2]);
static int	get_row_len(char **strs);

void	map_parsing(char *file_name, t_vars *vars, int case_size, int z_size)
{
	get_col_len(file_name, vars->map.size);
	set_coord(&vars->map, file_name);
	set_case_size(vars, case_size, z_size);
	set_default_param(vars);
	vars->map.angle.alpha = -2;
	vars->map.angle.beta = 2;
	vars->map.angle.gamma = 3;
}

static void	get_col_len(char *file_name, int size[2])
{
	char	*str;
	char	**strs;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	size[0] = 0;
	while (TRUE)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		if (size[0] == 0)
		{
			strs = ft_split(str, ' ');
			size[1] = get_row_len(strs);
		}
		free(str);
		size[0]++;
	}
	close(fd);
}

static int	get_row_len(char **strs)
{
	int	row_len;

	row_len = 0;
	while (strs[row_len])
	{
		free(strs[row_len]);
		row_len++;
	}
	free(strs);
	return (row_len);
}
