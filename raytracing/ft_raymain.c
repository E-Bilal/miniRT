/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raymain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:43:11 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 12:28:55 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static bool	hit_spheres(t_vec origin, t_vec ray, t_scene scene, t_hit *obj)
{
	int		i;
	bool	sphere_status;

	sphere_status = false;
	i = 0;
	while (i < scene.sp_index)
	{
		if (hit_sphere(origin, ray, obj, scene.sp[i]) == true)
		{
			sphere_status = true;
			obj->index = i;
			obj->type = 's';
		}
		i++;
	}
	return (sphere_status);
}

static bool	hit_planes(t_vec origin, t_vec ray, t_scene scene, t_hit *obj)
{
	int		i;
	bool	plane_status;

	plane_status = false;
	i = 0;
	while (i < scene.pl_index)
	{
		if (hit_plane(origin, ray, obj, scene.pl[i]) == true)
		{
			plane_status = true;
			obj->index = i;
			obj->type = 'p';
		}
		i++;
	}
	return (plane_status);
}

static bool	hit_cylnders(t_vec origin, t_vec ray, t_scene scene, t_hit *obj)
{
	int		i;
	bool	cylinder_status;

	cylinder_status = false;
	i = 0;
	while (i < scene.cy_index)
	{
		if (hit_cylinder(origin, ray, obj, scene.cy[i]) == true)
		{
			cylinder_status = true;
			obj->index = i;
			obj->type = 'c';
		}
		i++;
	}
	return (cylinder_status);
}

bool	hit_scene(t_vec origin, t_vec ray, t_scene scene, t_hit *obj)
{
	bool	hit_status;
	bool	sphere_status;
	bool	plane_status;
	bool	cylinder_status;

	hit_status = false;
	obj->t = (float)LONG_MAX;
	sphere_status = hit_spheres(origin, ray, scene, obj);
	plane_status = hit_planes(origin, ray, scene, obj);
	cylinder_status = hit_cylnders(origin, ray, scene, obj);
	if (sphere_status == true)
		hit_status = true;
	if (plane_status == true)
		hit_status = true;
	if (cylinder_status == true)
		hit_status = true;
	return (hit_status);
}

void	send_rays(t_scene scene, t_viewport vp, t_img *img, t_hit obj)
{
	t_vec	origin;
	float	x;
	float	y;

	printf("-----SENDING RAYS----\n");
	y = 0;
	origin = initvector(scene.cam.crd.x, scene.cam.crd.y, scene.cam.crd.z);
	while (y < vp.res_y)
	{
		x = 0;
		while (x < vp.res_x)
		{
			if (hit_scene(origin, create_ray(scene, vp, x, y), scene, &obj))
			{
				calc_shadowlight(origin,
					create_ray(scene, vp, x, y), scene, &obj);
				draw_pixel(img, x, y,
					set_color(obj, scene, scene.ambl, scene.light));
			}
			x++;
		}
		y++;
	}
	printf("----FINISHED SENDING RAYS----\n");
}
