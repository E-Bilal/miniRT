/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:10:12 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 16:52:57 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

float	ft_signum(float nbr)
{
	float	result;

	result = 0;
	if (nbr < 0)
		result = -1;
	if (nbr > 0)
		result = 1;
	if (nbr == 0)
		result = 0;
	return (result);
}

t_vec	normalize(t_vec v1)
{
	t_vec	result;
	float	magnitude;

	magnitude = sqrtf(powf(v1.x, 2) + powf(v1.y, 2) + powf(v1.z, 2));
	result.x = v1.x / magnitude;
	result.y = v1.y / magnitude;
	result.z = v1.z / magnitude;
	return (result);
}

float	magnitude(t_vec v1)
{
	float	magnitude;

	magnitude = sqrt(pow(v1.x, 2) + pow(v1.y, 2) + pow(v1.z, 2));
	return (magnitude);
}

float	dot(t_vec v1, t_vec v2)
{
	float	result;

	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return (result);
}

t_vec	cross(t_vec v1, t_vec v2)
{
	t_vec	result;

	result.x = ((v1.y * v2.z) - (v1.z * v2.y));
	result.y = ((v1.z * v2.x) - (v1.x * v2.z));
	result.z = ((v1.x * v2.y) - (v1.y * v2.x));
	return (result);
}
