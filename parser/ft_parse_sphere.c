/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:53:45 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 13:16:03 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	initsphere(t_sphere *sp)
{
	sp->crd = initcrd(0, 0, 0);
	sp->c = initcolor(0, 0, 0);
	sp->dia = 0;
}

static int	check_limit(int sp_index)
{
	if (sp_index >= 50)
	{
		write(1, "Error\nOnly a maximum of 50 spheres allowed.\n", 45);
		return (-1);
	}
	return (1);
}

int	parse_diameter(char **arr, t_scene *scene)
{
	int	status;
	int	i;

	status = 0;
	scene->sp[scene->sp_index].dia = 0;
	i = (*scene).sp_index;
	status += ft_atof(arr[2], &scene->sp[i].dia);
	if (status != 0)
	{
		write(1, "diameter of the sphere", 23);
		write(1, " has the wrong data type or is wrongly formatted.\n", 51);
		return (-1);
	}
	if (scene->sp[i].dia <= 0)
	{
		write(1, "Error\ndiameter has a negative or 0 value.\n", 43);
		return (-1);
	}
	if (scene->sp[i].dia > 200)
	{
		write(1, "Error\ndiameter can't have a value bigger than 200.\n ", 53);
		return (-1);
	}
	return (1);
}

int	parse_sphere(char **arr, t_scene *scene)
{
	int	i;
	int	sp_index;

	sp_index = scene->sp_index;
	initsphere(&scene->sp[sp_index]);
	i = 0;
	while (arr[i])
		i++;
	if (i != 4)
	{
		write (1, "4 set of values are neccessary for the sphere.\n", 48);
		return (-1);
	}
	if (check_limit(sp_index) == -1)
		return (-1);
	if (parse_crd(arr, &scene->sp[sp_index].crd) == -1)
		return (-1);
	if (parse_color(arr, &scene->sp[sp_index].c) == -1)
		return (-1);
	if (parse_diameter(arr, scene) == -1)
		return (-1);
	scene->sp_index++;
	return (0);
}
