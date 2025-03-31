/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 06:34:27 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 12:20:24 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	set_color(t_hit obj, t_scene scene, t_ambl amb, t_light light)
{
	float	resultr;
	float	resultg;
	float	resultb;
	t_color	color;

	if (obj.type == 's')
		color = scene.sp[obj.index].c;
	if (obj.type == 'p')
		color = scene.pl[obj.index].c;
	if (obj.type == 'c')
		color = scene.cy[obj.index].c;
	if (obj.light_angle < 0)
		obj.light_angle = 0;
	resultr = obj.light_angle * light.bright * color.r + amb.ambl_r * amb.c.r;
	if (resultr > 255)
		resultr = 255;
	resultg = obj.light_angle * light.bright * color.g + amb.ambl_r * amb.c.g;
	if (resultg > 255)
		resultg = 255;
	resultb = obj.light_angle * light.bright * color.b + amb.ambl_r * amb.c.b;
	if (resultb > 255)
		resultb = 255;
	return (((int)resultr << 16) | ((int)resultg << 8) | (int)resultb);
}
