/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:53:45 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 13:04:04 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	initlight(t_light *light)
{
	light->bright = 0;
	light->crd.x = 0;
	light->crd.y = 0;
	light->crd.z = 0;
	light->c.r = 0;
	light->c.g = 0;
	light->c.b = 0;
}

int	parse_brightness(char **arr, t_scene *scene)
{
	int	status;

	status = 0;
	status += ft_atof(arr[2], &scene->light.bright);
	if (status != 0)
	{
		write(1, "Brightness", 11);
		write(1, " has the wrong data type or is wrongly formatted.\n", 51);
		return (-1);
	}
	if (scene->light.bright > 1 || scene->light.bright < 0)
	{
		write(1, "Light brightness is out of range.\n", 35);
		return (-1);
	}
	return (1);
}

int	parse_light(char **arr, t_scene *scene)
{
	int	i;

	i = 0;
	initlight(&scene->light);
	if (scene->light_limit == 1)
	{
		write (1, "Only 1 light source is allowed.\n", 33);
		return (-1);
	}
	while (arr[i])
		i++;
	if (i != 4)
	{
		write (1, "4 set of values are neccessary for the light source.\n", 54);
		return (-1);
	}
	if (parse_crd(arr, &scene->light.crd) == -1)
		return (-1);
	if (parse_color(arr, &scene->light.c) == -1)
		return (-1);
	if (parse_brightness(arr, scene) == -1)
		return (-1);
	scene->light_limit++;
	return (0);
}
