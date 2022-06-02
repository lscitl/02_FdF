/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_math_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:07:34 by seseo             #+#    #+#             */
/*   Updated: 2022/05/12 16:56:30 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cross_product(double a[3], double b[3], double result[3])
{
	result[0] = a[1] * b[2] - a[2] * b[1];
	result[1] = a[2] * b[0] - a[0] * b[2];
	result[2] = a[0] * b[1] - a[1] * b[0];
}

double	dot_product(double a[3], double b[3])
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

double	vector_size(double a[3])
{
	return (sqrtl(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]));
}

void	make_unit_vector(double a[3])
{
	double	size;

	size = vector_size(a);
	a[0] /= size;
	a[1] /= size;
	a[2] /= size;
}

double	get_angle(double a[3], double b[3])
{
	const double	dot_val = dot_product(a, b);
	const double	a_size = vector_size(a);
	const double	b_size = vector_size(b);

	return (acos(dot_val / (a_size * b_size)));
}
