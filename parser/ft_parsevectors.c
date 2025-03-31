/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsevectors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 05:48:14 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 13:19:11 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static int	check_normvec(t_vec vec)
{
	float	sum;

	if (vec.x > 1 || vec.x < -1)
		return (-1);
	if (vec.y > 1 || vec.y < -1)
		return (-1);
	if (vec.z > 1 || vec.z < -1)
		return (-1);
	sum = powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2);
	if (sum > 1.05 || sum < 0.995)
		return (-1);
	return (1);
}

static void	ft_free_vec(char **arr)
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

static int	ft_write_error(int type, char **vec)
{
	if (type == 1)
	{
		write(1, "Something went wrong with splitting the vectors.\n", 50);
	}
	else if (type == 2)
	{
		write(1, "3 vector directions are needed.\n", 33);
		ft_free_vec(vec);
	}
	else if (type == 3)
	{
		write(1, "Sum of squared vec directions not equal to 1 or -1\n", 52);
	}
	else if (type == 4)
	{
		write(1, "One of the vector directions", 29);
		write(1, " has the wrong data type or is wrongly formatted.\n", 51);
	}
	return (-1);
}

int	parse_vec(char **arr, t_vec *vec)
{
	int		status;
	char	**split_vec;
	int		i;

	status = 0;
	i = 0;
	split_vec = ft_split(arr[2], ',');
	if (split_vec == NULL)
		return (ft_write_error(1, NULL));
	while (split_vec[i])
		i++;
	if (i != 3)
		return (ft_write_error(2, split_vec));
	status += ft_atof(split_vec[0], &vec->x);
	status += ft_atof(split_vec[1], &vec->y);
	status += ft_atof(split_vec[2], &vec->z);
	ft_free_vec(split_vec);
	if (check_normvec(*vec) == -1)
		return (ft_write_error(3, NULL));
	if (status != 0)
		return (ft_write_error(4, NULL));
	return (1);
}
