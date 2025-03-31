/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 03:26:19 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 12:23:45 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	ft_inverse_camlight(t_scene *scene)
{
	scene->light.crd.z *= -1;
	scene->light.crd.x *= -1;
	scene->cam.v.z *= -1;
	scene->cam.v.x *= -1;
}

static void	ft_inverse_crdvec(t_scene *scene)
{
	int	i;

	ft_inverse_camlight(scene);
	i = -1;
	while (++i < scene->sp_index)
	{
		scene->sp[i].crd.z *= -1;
		scene->sp[i].crd.x *= -1;
	}
	i = -1;
	while (++i < scene->pl_index)
	{
		scene->pl[i].crd.z *= -1;
		scene->pl[i].v.z *= -1;
		scene->pl[i].crd.x *= -1;
		scene->pl[i].v.x *= -1;
	}
	i = -1;
	while (++i < scene->cy_index)
	{
		scene->cy[i].crd.z *= -1;
		scene->cy[i].v.z *= -1;
		scene->cy[i].crd.x *= -1;
		scene->cy[i].v.x *= -1;
	}
}

void	ft_offsetcam_vec(t_scene *scene)
{
	int		i;
	t_quat	q_rot;

	if (scene->cam.v.z > 0)
		ft_inverse_crdvec(scene);
	q_rot = create_quaternion(scene->cam.v);
	scene->cam.v = rotate_vec(scene->cam.v, q_rot);
	i = -1;
	while (++i < scene->sp_index)
	{
		scene->sp[i].crd = rotate_crd(scene->sp[i].crd, q_rot);
	}
	i = -1;
	while (++i < scene->pl_index)
	{
		scene->pl[i].crd = rotate_crd(scene->pl[i].crd, q_rot);
		scene->pl[i].v = rotate_vec(scene->pl[i].v, q_rot);
	}
	i = -1;
	while (++i < scene->cy_index)
	{
		scene->cy[i].crd = rotate_crd(scene->cy[i].crd, q_rot);
		scene->cy[i].v = rotate_vec(scene->cy[i].v, q_rot);
	}
	scene->light.crd = rotate_crd(scene->light.crd, q_rot);
}

void	ft_offsetcam_crd(t_scene *scene)
{
	int		i;
	t_crd	offset;

	offset = scene->cam.crd;
	scene->cam.crd = offsetcrd(scene->cam.crd, offset);
	scene->light.crd = offsetcrd(scene->light.crd, offset);
	i = -1;
	while (++i < scene->sp_index)
		scene->sp[i].crd = offsetcrd(scene->sp[i].crd, offset);
	i = -1;
	while (++i < scene->pl_index)
		scene->pl[i].crd = offsetcrd(scene->pl[i].crd, offset);
	i = -1;
	while (++i < scene->cy_index)
		scene->cy[i].crd = offsetcrd(scene->cy[i].crd, offset);
}
