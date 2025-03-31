/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_arithmetic.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 00:06:38 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 17:18:06 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec	vecadditon(t_vec v1, t_vec v2)
{
	t_vec	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vec	vecsubtract(t_vec v1, t_vec v2)
{
	t_vec	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vec	vecmutiply(float multiplier, t_vec v1)
{
	t_vec	result;

	result.x = v1.x * multiplier;
	result.y = v1.y * multiplier;
	result.z = v1.z * multiplier;
	return (result);
}

t_vec	vecdivision(float divisor, t_vec v1)
{
	t_vec	result;

	result.x = v1.x / divisor;
	result.y = v1.y / divisor;
	result.z = v1.z / divisor;
	return (result);
}
