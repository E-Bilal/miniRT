/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_viewport.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:03:21 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 12:49:52 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	init_viewport(t_viewport *vp)
{
	vp->backvector = initvector(0, 0, 0);
	vp->pixel_delta_x = initvector(0, 0, 0);
	vp->pixel_delta_y = initvector(0, 0, 0);
	vp->rightvector = initvector(0, 0, 0);
	vp->top_leftpixel = initvector(0, 0, 0);
	vp->upvector = initvector(0, 0, 0);
	vp->viewport_vecx = initvector(0, 0, 0);
	vp->viewport_vecy = initvector(0, 0, 0);
	vp->viewport_x = 0;
	vp->viewport_y = 0;
}

static void	create_camera_vectors(t_scene scene, t_viewport *vp)
{
	t_vec	lookat;
	t_vec	upguide;

	upguide = initvector(0, 1, 0);
	lookat = veccrdadditon(scene.cam.v, scene.cam.crd);
	vp->backvector = normalize(crdvecsubtract(scene.cam.crd, lookat));
	vp->rightvector = normalize(cross(upguide, vp->backvector));
	vp->upvector = cross(vp->backvector, vp->rightvector);
}

static void	set_viewport_dimensions(t_scene *scene, t_viewport *vp)
{
	float	fov;

	fov = tan(((scene->cam.fov * M_PI) / 180) / 2);
	vp->viewport_y = 2 * fov * 1;
	vp->viewport_x = vp->viewport_y * ((float)vp->res_x) / (float)vp->res_y;
	vp->viewport_vecx = vecmutiply(vp->viewport_x, vp->rightvector);
	vp->viewport_vecy = vecmutiply((vp->viewport_y * -1), vp->upvector);
}

static void	set_00pixel(t_scene *scene, t_viewport *vp)
{
	t_vec	pixel_delta_xy;

	pixel_delta_xy = vecadditon(vp->pixel_delta_x, vp->pixel_delta_y);
	pixel_delta_xy = vecmutiply(0.5, pixel_delta_xy);
	vp->pixel_delta_x = vecdivision((float)vp->res_x, vp->viewport_vecx);
	vp->pixel_delta_y = vecdivision((float)vp->res_y, vp->viewport_vecy);
	vp->top_leftpixel = crdvecsubtract(scene->cam.crd, vp->backvector);
	vp->top_leftpixel = vecsubtract(vp->top_leftpixel,
			vecdivision(2, vp->viewport_vecx));
	vp->top_leftpixel = vecsubtract(vp->top_leftpixel,
			vecdivision(2, vp->viewport_vecy));
	vp->top_leftpixel = vecadditon(vp->top_leftpixel, pixel_delta_xy);
}

void	create_viewport(t_scene *scene, t_viewport *vp)
{
	init_viewport(vp);
	create_camera_vectors(*scene, vp);
	set_viewport_dimensions(scene, vp);
	set_00pixel(scene, vp);
}
