/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsecolors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:53:58 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 13:08:43 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	ft_free_color(char **arr)
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

static int	ft_write_error(int type, char **color)
{
	if (type == 1)
		write(1, "Something went wrong with splitting the colors.\n", 49);
	else if (type == 2)
	{
		write(1, "3 color components are needed.\n", 32);
		ft_free_color(color);
	}
	else if (type == 3)
		write(1, "One of the color components is out of range.\n", 46);
	else if (type == 4)
	{
		write(1, "One of the color components", 28);
		write(1, " has the wrong data type or is wrongly formatted.\n", 51);
	}
	return (-1);
}

static int	check_color(t_color color)
{
	if (color.r > 255 || color.r < 0)
		return (-1);
	if (color.g > 255 || color.g < 0)
		return (-1);
	if (color.b > 255 || color.b < 0)
		return (-1);
	return (1);
}

static int	get_color_index(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	i--;
	return (i);
}

int	parse_color(char **arr, t_color *color)
{
	int		status;
	char	**split_color;
	int		i;

	status = 0;
	i = get_color_index(arr);
	split_color = ft_split(arr[i], ',');
	if (split_color == NULL)
		return (ft_write_error(1, NULL));
	i = 0;
	while (split_color[i])
		i++;
	if (i != 3)
		return (ft_write_error(2, split_color));
	status += ft_atoi(split_color[0], &color->r);
	status += ft_atoi(split_color[1], &color->g);
	status += ft_atoi(split_color[2], &color->b);
	ft_free_color(split_color);
	if (status != 0)
		return (ft_write_error(4, NULL));
	if (check_color(*color) == -1)
		return (ft_write_error(3, NULL));
	return (1);
}
