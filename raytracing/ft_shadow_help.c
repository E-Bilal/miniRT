/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:16:22 by senayat           #+#    #+#             */
/*   Updated: 2024/11/25 12:16:35 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static bool	point_in_cylinder_check(
	t_vec ra, t_vec rb, t_vec point, float radius)
{
	t_vec	e;
	float	d;
	float	capap;
	float	capbp;

	e = vecsubtract(rb, ra);
	d = magnitude(cross(e, vecsubtract(point, ra))) / magnitude(e);
	capap = dot(vecsubtract(point, ra), vecmutiply(-1, e));
	capbp = dot(vecsubtract(point, rb), vecmutiply(1, e));
	if (d <= radius && capap <= 0 && capbp <= 0)
		return (true);
	return (false);
}

bool	point_in_cylinder(t_vec point, t_cylinder cylinder)
{
	t_vec	ra;
	t_vec	rb;
	float	radius;

	radius = cylinder.dia / 2;
	ra.x = cylinder.crd.x + (cylinder.v.x * (cylinder.height / 2));
	ra.y = cylinder.crd.y + (cylinder.v.y * (cylinder.height / 2));
	ra.z = cylinder.crd.z + (cylinder.v.z * (cylinder.height / 2));
	rb.x = cylinder.crd.x - (cylinder.v.x * (cylinder.height / 2));
	rb.y = cylinder.crd.y - (cylinder.v.y * (cylinder.height / 2));
	rb.z = cylinder.crd.z - (cylinder.v.z * (cylinder.height / 2));
	return (point_in_cylinder_check(ra, rb, point, radius));
}
