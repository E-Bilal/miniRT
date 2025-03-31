/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsecoordinates.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 03:10:51 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 16:15:27 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	ft_free_crd(char **arr)
{
	int	i;

	if (arr != NULL)
	{
		i = -1;
		while (arr[++i])
			free((arr[i]));
		free(arr);
	}
}

static int	check_coordinates(t_crd crd)
{
	if (crd.x > 1000 || crd.x < -1000)
		return (-1);
	if (crd.y > 1000 || crd.y < -1000)
		return (-1);
	if (crd.z > 1000 || crd.z < -1000)
		return (-1);
	return (1);
}

static int	ft_write_error(int type, char **crd)
{
	if (type == 1)
	{
		write(1, "Something went wrong with splitting the coordinates\n", 53);
	}
	else if (type == 2)
	{
		write(1, "3 coordinates are needed.\n", 25);
		ft_free_crd(crd);
	}
	else if (type == 3)
	{
		write(1, "One of the coordinates has the wrong", 37);
		write(1, " data type or is wrongly formatted.\n", 37);
	}
	else if (type == 4)
	{
		write(1, "One of the coordinates is out of the set range.\n", 49);
	}
	return (-1);
}

int	parse_crd(char **arr, t_crd *crd)
{
	int		status;
	char	**split_crd;
	int		i;

	i = 0;
	status = 0;
	split_crd = ft_split(arr[1], ',');
	if (split_crd == NULL)
		return (ft_write_error(1, NULL));
	while (split_crd[i])
		i++;
	if (i != 3)
		return (ft_write_error(2, split_crd));
	status += ft_atof(split_crd[0], &crd->x);
	status += ft_atof(split_crd[1], &crd->y);
	status += ft_atof(split_crd[2], &crd->z);
	ft_free_crd(split_crd);
	if (status != 0)
		return (ft_write_error(3, NULL));
	if (check_coordinates(*crd) == -1)
		return (ft_write_error(4, NULL));
	return (1);
}
