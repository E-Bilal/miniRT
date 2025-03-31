/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:16:23 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 12:17:01 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	shadowlight_sp(t_hit *obj, t_hit *shadowobj, t_scene scene)
{
	int		i;
	t_vec	shadowray;
	float	dist_light;

	i = 0;
	shadowray = crdvecsubtract(scene.light.crd, obj->hitpoint);
	dist_light = sqrtf(dot(shadowray, shadowray));
	while (i < scene.sp_index)
	{
		if (hit_sphere(obj->hitpoint, shadowray, shadowobj, scene.sp[i]))
		{
			if (shadowobj->t < dist_light)
			{
				obj->light_angle = 0;
				obj->edgecase_status = 1;
				return ;
			}
		}
		i++;
	}
	if (obj->light_angle <= 0.02)
		obj->light_angle = 0;
}

static void	shadowlight_pl(t_hit *obj, t_hit *shadowobj, t_scene scene)
{
	int		i;
	t_vec	shadowray;
	float	dist_light;

	i = 0;
	shadowray = crdvecsubtract(scene.light.crd, obj->hitpoint);
	dist_light = sqrtf(dot(shadowray, shadowray));
	while (i < scene.pl_index)
	{
		if (point_in_plane(scene.pl[i], scene.cam.crd))
			i++;
		else if (hit_plane(obj->hitpoint, shadowray, shadowobj, scene.pl[i]))
		{
			if (shadowobj->t < dist_light)
				obj->light_angle = 0;
		}
		i++;
	}
}

static void	shadowlight_cy(t_hit *obj, t_hit *shadowobj, t_scene scene)
{
	int		i;
	t_vec	shadowray;
	float	dist_light;

	i = 0;
	shadowray = crdvecsubtract(scene.light.crd, obj->hitpoint);
	dist_light = sqrtf(dot(shadowray, shadowray));
	while (i < scene.cy_index)
	{
		if (obj->index == i && obj->type == 'c')
			i = i;
		if (hit_cylinder(obj->hitpoint, shadowray, shadowobj, scene.cy[i]))
			if (shadowobj->t < dist_light)
				obj->light_angle = 0;
		i++;
	}
}

static void	edgecase(t_vec origin, t_hit *obj, t_scene scene)
{
	t_vec	light;
	t_hit	shadow_obj;

	light = initvector(scene.light.crd.x, scene.light.crd.y, scene.light.crd.z);
	if (point_in_cylinder(origin, scene.cy[obj->index]) == true)
	{
		if (point_in_cylinder(light, scene.cy[obj->index]) == true)
		{
			shadowlight_sp(obj, &shadow_obj, scene);
			if (shadow_obj.edgecase_status != 1)
				obj->light_angle = 1;
		}
		if (point_in_cylinder(light, scene.cy[obj->index]) == false)
			obj->light_angle = 0;
	}
}

void	calc_shadowlight(t_vec origin, t_vec ray, t_scene scene, t_hit *obj)
{
	t_hit	shadow_obj;
	t_vec	light_vec;

	if (obj->type == 's')
		sphere_normal(origin, ray, obj, scene.sp[obj->index]);
	if (obj->type == 'p')
		plane_normal(origin, ray, obj, scene.pl[obj->index]);
	if (obj->type == 'c')
		obj->normal = normalize(obj->normal);
	obj->t = (float)LONG_MAX;
	shadow_obj.t = (float)LONG_MAX;
	light_vec = normalize(vecrdsubtract(obj->hitpoint, scene.light.crd));
	obj->light_angle = dot(obj->normal, light_vec) * -1;
	shadowlight_sp(obj, &shadow_obj, scene);
	shadowlight_pl(obj, &shadow_obj, scene);
	shadowlight_cy(obj, &shadow_obj, scene);
	if (obj->type == 'c')
		edgecase(origin, obj, scene);
	if (light_and_cam_in_plane(scene) == true)
		obj->light_angle = 0;
}
