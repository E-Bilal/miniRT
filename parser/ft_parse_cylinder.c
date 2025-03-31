/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:14:53 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 13:22:16 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	initcylinder(t_cylinder *cy)
{
	cy->crd.x = 0;
	cy->crd.y = 0;
	cy->crd.z = 0;
	cy->v.x = 0;
	cy->v.y = 0;
	cy->v.z = 0;
	cy->c.r = 0;
	cy->c.g = 0;
	cy->c.b = 0;
	cy->dia = 0;
	cy->height = 0;
}

static int	ft_write_error(int type)
{
	if (type == 1)
	{
		write (1, "Error\n6 set of values ", 23);
		write (1, "are neccessary for the cylinder.\n", 34);
	}
	if (type == 2)
	{
		write(1, "Error\ndiameter of the cylinder", 31);
		write(1, " has the wrong data type or is wrongly formatted.\n", 51);
	}
	if (type == 3)
	{
		write(1, "Error\ndiameter of the cylinder", 31);
		write(1, " has the wrong data type or is wrongly formatted.\n", 51);
	}
	if (type == 4)
		write(1, "Error\ndiameter or height has a negative or 0 value.\n", 53);
	if (type == 5)
	{
		write(1, "Error\ndiameter or height ", 26);
		write(1, "can't have a value bigger than 200.\n", 37);
	}
	return (-1);
}

static int	check_limit(int cy_index)
{
	if (cy_index >= 50)
	{
		write(1, "Error\nOnly a maximum of 50 cylinders allowed.\n", 47);
		return (-1);
	}
	return (1);
}

static int	parse_dimensions(char **arr, t_scene *scene)
{
	int	status;
	int	i;

	status = 0;
	i = (*scene).cy_index;
	status = ft_atof(arr[4], &scene->cy[i].height);
	if (status == -1)
		return (ft_write_error(2));
	status = 0;
	status = ft_atof(arr[3], &scene->cy[i].dia);
	if (status == -1)
		return (ft_write_error(3));
	if (scene->cy[i].dia <= 0 || scene->cy[i].height <= 0)
		return (ft_write_error(4));
	if (scene->cy[i].dia > 200 || scene->cy[i].height > 200)
		return (ft_write_error(5));
	return (1);
}

int	parse_cylinder(char **arr, t_scene *scene)
{
	int	i;
	int	cy_index;

	cy_index = scene->cy_index;
	initcylinder(&scene->cy[cy_index]);
	i = 0;
	while (arr[i])
		i++;
	if (i != 6)
		return (ft_write_error(1));
	if (check_limit(cy_index) == -1)
		return (-1);
	if (parse_crd(arr, &scene->cy[cy_index].crd) == -1)
		return (-1);
	if (parse_vec(arr, &scene->cy[cy_index].v) == -1)
		return (-1);
	if (parse_dimensions(arr, scene) == -1)
		return (-1);
	if (parse_color(arr, &scene->cy[cy_index].c) == -1)
		return (-1);
	scene->cy_index++;
	return (0);
}
