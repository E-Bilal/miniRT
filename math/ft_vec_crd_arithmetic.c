/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_crd_arithmetic.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 02:21:07 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 17:19:33 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec	veccrdadditon(t_vec v1, t_crd v2)
{
	t_vec	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vec	crdvecsubtract(t_crd crd, t_vec v2)
{
	t_vec	result;

	result.x = crd.x - v2.x;
	result.y = crd.y - v2.y;
	result.z = crd.z - v2.z;
	return (result);
}

t_vec	vecrdsubtract(t_vec v, t_crd crd)
{
	t_vec	result;

	result.x = v.x - crd.x;
	result.y = v.y - crd.y;
	result.z = v.z - crd.z;
	return (result);
}

t_crd	offsetcrd(t_crd crd, t_crd offset)
{
	t_crd	result;

	result.x = crd.x - offset.x;
	result.y = crd.y - offset.y;
	result.z = crd.z - offset.z;
	return (result);
}

t_vec	convert_crd_to_vec(t_crd crd)
{
	t_vec	result;

	result.x = crd.x;
	result.y = crd.y;
	result.z = crd.z;
	return (result);
}
