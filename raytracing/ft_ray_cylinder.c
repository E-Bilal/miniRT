/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:28:54 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 12:46:19 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static t_vec	initcap(t_cylinder cylinder, char type)
{
	t_vec	result;

	if (type == 'a')
	{
		result.x = cylinder.crd.x + (cylinder.v.x * (cylinder.height / 2));
		result.y = cylinder.crd.y + (cylinder.v.y * (cylinder.height / 2));
		result.z = cylinder.crd.z +(cylinder.v.z * (cylinder.height / 2));
	}
	else if (type == 'b')
	{
		result.x = cylinder.crd.x - (cylinder.v.x * (cylinder.height / 2));
		result.y = cylinder.crd.y -(cylinder.v.y * (cylinder.height / 2));
		result.z = cylinder.crd.z -(cylinder.v.z * (cylinder.height / 2));
	}
	return (result);
}

static bool	cy_discriminant(t_ray_cy *cy, t_vec oc, t_vec ray)
{
	float	c;
	float	rapow;

	rapow = (powf(cy->ra, 2) * cy->baba);
	cy->a = cy->baba - (cy->bard * cy->bard);
	cy->b = (cy->baba * dot(oc, ray)) - (cy->baoc * cy->bard);
	c = (cy->baba * dot(oc, oc)) - (cy->baoc * cy->baoc) - rapow;
	cy->discriminant = (cy->b * cy->b) - (cy->a * c);
	if (cy->discriminant < 0)
		return (false);
	cy->discriminant = sqrtf(cy->discriminant);
	cy->body_t1 = (-cy->b - cy->discriminant) / cy->a;
	cy->body_t2 = (-cy->b + cy->discriminant) / cy->a;
	cy->height1 = cy->baoc + (cy->body_t1 * cy->bard);
	if (cy->height1 < 0)
		cy->cap_t1 = (0 - cy->baoc) / cy->bard;
	else
		cy->cap_t1 = (cy->baba - cy->baoc) / cy->bard;
	cy->height2 = cy->baoc + (cy->body_t2 * cy->bard);
	if (cy->height2 < 0)
		cy->cap_t2 = (0 - cy->baoc) / cy->bard;
	else
		cy->cap_t2 = (cy->baba - cy->baoc) / cy->bard;
	return (true);
}

static bool	cy_firsthit(t_vec ray, t_vec oc, t_hit *obj, t_ray_cy cy)
{
	t_vec	temp;

	if (cy.height1 > 0 && cy.height1 < cy.baba)
	{
		if (cy.body_t1 < obj->t && cy.body_t1 > 0.01)
		{
			obj->t = cy.body_t1;
			temp = vecadditon(oc, vecmutiply(obj->t, ray));
			obj->normal = vecmutiply(cy.height1, cy.ba);
			obj->normal = vecdivision(cy.baba, obj->normal);
			obj->normal = vecdivision(cy.ra, vecsubtract(temp, obj->normal));
			return (true);
		}
	}
	if (fabs(cy.b + cy.a * cy.cap_t1) < cy.discriminant && cy.cap_t1 > 0.01)
	{
		if (cy.cap_t1 < obj->t)
		{
			obj->t = cy.cap_t1;
			obj->normal = vecmutiply(ft_signum(cy.height1), cy.ba);
			obj->normal = vecdivision(sqrtf(cy.baba), obj->normal);
			return (true);
		}
	}
	return (false);
}

static bool	cy_secondhit(t_crd crd, t_hit *obj, t_ray_cy cy)
{
	if (cy.height2 > 0 && cy.height2 < cy.baba)
	{
		if (cy.body_t2 < obj->t && cy.body_t2 > 0.01)
		{
			obj->t = cy.body_t2;
			obj->normal = vecrdsubtract(obj->hitpoint, crd);
			obj->normal = vecmutiply(-1, obj->normal);
			return (true);
		}
	}
	if (fabs(cy.b + cy.a * cy.cap_t2) < cy.discriminant && cy.cap_t2 > 0.01)
	{
		if (cy.cap_t2 < obj->t)
		{
			obj->t = cy.cap_t2;
			obj->normal = vecmutiply(ft_signum(cy.height1), cy.ba);
			obj->normal = vecdivision(sqrtf(cy.baba), obj->normal);
			return (true);
		}
	}
	return (false);
}

bool	hit_cylinder(t_vec origin, t_vec ray, t_hit *obj, t_cylinder cylinder)
{
	t_ray_cy	cy;
	t_vec		oc;

	cy.ra = cylinder.dia / 2;
	ray = normalize(ray);
	cy.ba = vecsubtract(initcap(cylinder, 'b'), initcap(cylinder, 'a'));
	oc = vecsubtract(origin, initcap(cylinder, 'a'));
	cy.baba = dot(cy.ba, cy.ba);
	cy.bard = dot(cy.ba, ray);
	cy.baoc = dot(cy.ba, oc);
	if (cy_discriminant(&cy, oc, ray) == false)
		return (false);
	if (cy_firsthit(ray, oc, obj, cy) == true)
	{
		obj->hitpoint = vecadditon(origin, vecmutiply(obj->t, ray));
		return (true);
	}
	if (cy_secondhit(cylinder.crd, obj, cy) == true)
	{
		obj->hitpoint = vecadditon(origin, vecmutiply(obj->t, ray));
		return (true);
	}
	return (false);
}
