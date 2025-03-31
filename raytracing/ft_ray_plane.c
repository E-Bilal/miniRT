/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:15:30 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 12:32:27 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	plane_normal(t_vec origin, t_vec ray, t_hit *obj, t_plane pl)
{
	ray = normalize(ray);
	obj->hitpoint = vecadditon(origin, vecmutiply(obj->t, ray));
	obj->normal = normalize(pl.v);
	if (dot(ray, pl.v) > 0.01)
		obj->normal = vecmutiply(-1, obj->normal);
}

bool	point_in_plane(t_plane plane, t_crd origin)
{
	float	x;
	float	y;
	float	z;
	float	result;

	x = plane.v.x * (origin.x - plane.crd.x);
	y = plane.v.y * (origin.y - plane.crd.y);
	z = plane.v.z * (origin.z - plane.crd.z);
	result = x + y + z;
	if (result < 0.5 && result > -0.5)
		return (true);
	return (false);
}

bool	light_and_cam_in_plane(t_scene scene)
{
	int	i;

	i = 0;
	while (i < scene.pl_index)
	{
		if (point_in_plane(scene.pl[i], scene.light.crd)
			&& !point_in_plane(scene.pl[i], scene.cam.crd))
			return (true);
		i++;
	}
	return (false);
}

bool	hit_plane(t_vec origin, t_vec ray, t_hit *shape, t_plane plane)
{
	float	hit1;
	float	hit2;
	float	t;
	t_vec	hitplane;

	hit2 = dot(plane.v, normalize(ray));
	hitplane = crdvecsubtract(plane.crd, origin);
	hit1 = dot(hitplane, plane.v);
	t = hit1 / hit2;
	if (t > 0.01)
	{
		if (t < shape->t)
		{
			shape->t = t;
			return (true);
		}
	}
	return (false);
}
