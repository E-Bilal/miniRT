/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_structs_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 04:29:14 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 10:19:35 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec	initvector(float x, float y, float z)
{
	t_vec	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_crd	initcrd(float x, float y, float z)
{
	t_crd	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_color	initcolor(int r, int g, int b)
{
	t_color	result;

	result.r = r;
	result.g = g;
	result.b = b;
	return (result);
}

void	ft_initdata(t_all_data *t)
{
	t->scene.amb_limit = 0;
	t->scene.cam_limit = 0;
	t->scene.light_limit = 0;
	t->scene.sp_index = 0;
	t->scene.pl_index = 0;
	t->scene.cy_index = 0;
	t->menu.value_i = 0;
	t->menu.value_f = 0;
}

void	ft_copyscene(t_scene *dest_scene, t_scene *src_scene)
{
	int	i;

	dest_scene->ambl = src_scene->ambl;
	dest_scene->cam = src_scene->cam;
	dest_scene->light = src_scene->light;
	dest_scene->sp_index = src_scene->sp_index;
	dest_scene->pl_index = src_scene->pl_index;
	dest_scene->cy_index = src_scene->cy_index;
	i = -1;
	while (++i < src_scene->sp_index)
		dest_scene->sp[i] = src_scene->sp[i];
	i = -1;
	while (++i < src_scene->pl_index)
		dest_scene->pl[i] = src_scene->pl[i];
	i = -1;
	while (++i < src_scene->cy_index)
		dest_scene->cy[i] = src_scene->cy[i];
}
