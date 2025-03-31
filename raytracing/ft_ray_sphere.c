/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 01:35:38 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 12:45:58 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	sphere_normal(t_vec origin, t_vec ray, t_hit *obj, t_sphere sp)
{
	float	radius;
	float	d;
	t_vec	os;

	ray = normalize(ray);
	obj->hitpoint = vecadditon(origin, vecmutiply(obj->t, ray));
	obj->normal = normalize(vecrdsubtract(obj->hitpoint, sp.crd));
	radius = sp.dia / 2;
	os = crdvecsubtract(sp.crd, origin);
	d = dot(os, os);
	if (d < (radius * radius))
	{
		obj->normal = vecmutiply(-1, obj->normal);
		return ;
	}
}

static bool	quadratic_solver(float a, float b, float c, float *t_hit)
{
	float	t1;
	float	t2;
	float	discriminant;

	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0.01)
		return (false);
	else if (discriminant > -0.01 && discriminant < 0.01)
	{
		*t_hit = -b / (2 * a);
		return (true);
	}
	t1 = (-b - sqrtf((b * b) - 4 * a * c)) / (2 * a);
	t2 = (-b + sqrtf((b * b) - 4 * a * c)) / (2 * a);
	if ((t1 < t2 && t1 >= 0.01) || (t1 > t2 && t2 <= 0.01))
	{
		*t_hit = t1;
		return (true);
	}
	else if (t2 >= 0.01)
	{
		*t_hit = t2;
		return (true);
	}
	return (false);
}

bool	hit_sphere(t_vec origin, t_vec ray, t_hit *sp, t_sphere sphere)
{
	t_vec	oc;
	float	a;
	float	b;
	float	c;
	float	t_close;

	ray = normalize(ray);
	oc = vecrdsubtract(origin, sphere.crd);
	a = dot(ray, ray);
	b = (float)2.0 * dot(oc, ray);
	c = dot(oc, oc) - (powf(sphere.dia / (float)2, 2));
	if (quadratic_solver(a, b, c, &t_close) == true)
	{
		if (sp->t > t_close)
		{
			sp->t = t_close;
			return (true);
		}
	}
	return (false);
}
