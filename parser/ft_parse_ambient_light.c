/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_ambient_light.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:53:45 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 16:25:38 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	initambient(t_ambl *ambl)
{
	ambl->ambl_r = 0;
	ambl->c.r = 0;
	ambl->c.g = 0;
	ambl->c.b = 0;
}

int	parse_ambience(char **arr, t_scene *scene)
{
	int	status;

	status = ft_atof(arr[1], &scene->ambl.ambl_r);
	if (status == -1)
	{
		write(1, "One of the values of ambient light", 35);
		write(1, " has the wrong data type or is wrongly formatted.\n", 51);
		return (-1);
	}
	if (scene->ambl.ambl_r > 1 || scene->ambl.ambl_r < 0)
	{
		write(1, "Ambient strength is out of range.\n", 35);
		return (-1);
	}
	return (1);
}

int	parse_ambientl(char **arr, t_scene *scene)
{
	int	i;

	i = 0;
	initambient(&scene->ambl);
	if (scene->amb_limit == 1)
	{
		write (1, "Only 1 ambience light source is allowed.\n", 42);
		return (-1);
	}
	while (arr[i])
		i++;
	if (i != 3)
	{
		write (1, "3 set of values are neccessary for ambient light.\n", 48);
		return (-1);
	}
	if (parse_color(arr, &scene->ambl.c) == -1)
		return (-1);
	if (parse_ambience(arr, scene) == -1)
		return (-1);
	scene->amb_limit++;
	return (0);
}
