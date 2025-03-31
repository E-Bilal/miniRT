/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:56:30 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 13:05:45 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	initplane(t_plane *pl)
{
	pl->crd = initcrd(0, 0, 0);
	pl->v = initvector(0, 0, 0);
	pl->c = initcolor(0, 0, 0);
}

static int	check_limit(int pl_index)
{
	if (pl_index >= 50)
	{
		write(1, "Error\nOnly a maximum of 50 planes allowed.\n", 44);
		return (-1);
	}
	return (1);
}

int	parse_plane(char **arr, t_scene *scene)
{
	int	i;
	int	pl_index;

	pl_index = scene->pl_index;
	initplane(&scene->pl[pl_index]);
	i = 0;
	while (arr[i])
		i++;
	if (i != 4)
	{
		write (1, "4 set of values are neccessary for the plane.\n", 47);
		return (-1);
	}
	if (check_limit(pl_index) == -1)
		return (-1);
	if (parse_crd(arr, &scene->pl[pl_index].crd) == -1)
		return (-1);
	if (parse_vec(arr, &scene->pl[pl_index].v) == -1)
		return (-1);
	if (parse_color(arr, &scene->pl[pl_index].c) == -1)
		return (-1);
	scene->pl_index++;
	return (0);
}
