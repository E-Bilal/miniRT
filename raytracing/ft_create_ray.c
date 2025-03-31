/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:14:40 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 12:35:30 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec	create_ray(t_scene scene, t_viewport vp, float x, float y)
{
	t_vec	ray_direction;
	t_vec	cur_pixel;

	cur_pixel = vecadditon(vp.top_leftpixel, vecmutiply(x, vp.pixel_delta_x));
	cur_pixel = vecadditon(cur_pixel, vecmutiply(y, vp.pixel_delta_y));
	ray_direction = vecrdsubtract(cur_pixel, scene.cam.crd);
	return (ray_direction);
}
