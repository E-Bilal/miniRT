/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:31:44 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 16:28:18 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	initcamera(t_camera *cam)
{
	cam->crd.x = 0;
	cam->crd.y = 0;
	cam->crd.z = 0;
	cam->v.x = 0;
	cam->v.y = 0;
	cam->v.z = 0;
	cam->fov = 0;
}

int	parse_fov(char **arr, t_scene *scene)
{
	int	status;

	status = 0;
	status += ft_atoi(arr[3], &scene->cam.fov);
	if (status != 0)
	{
		write(1, "FOV of the camera", 18);
		write(1, " has the wrong data type or is wrongly formatted.\n", 51);
		return (-1);
	}
	if (scene->cam.fov > 180 || scene->cam.fov < 0)
	{
		write(1, "FOV is out of range.\n", 22);
		return (-1);
	}
	return (1);
}

int	parse_cam(char **arr, t_scene *scene)
{
	int	i;

	i = 0;
	initcamera(&scene->cam);
	if (scene->cam_limit == 1)
	{
		write (1, "Only 1 camera is allowed.\n", 27);
		return (-1);
	}
	while (arr[i])
		i++;
	if (i != 4)
	{
		write (1, "4 set of values are neccessary for the camera.\n", 48);
		return (-1);
	}
	if (parse_crd(arr, &scene->cam.crd) == -1)
		return (-1);
	if (parse_vec(arr, &scene->cam.v) == -1)
		return (-1);
	if (parse_fov(arr, scene) == -1)
		return (-1);
	scene->cam_limit++;
	return (0);
}
