/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_to_number.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:20:33 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 16:19:06 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static int	ft_checknumber_float(char *str)
{
	int	dot;
	int	i;
	int	len;

	i = 0;
	dot = 0;
	len = ft_strlen(str);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i] && ((str[i] >= 48 && str[i] <= 57) || str[i] == '.'))
	{
		if (str[i] == 46)
			dot++;
		i++;
	}
	if (len != i || dot > 1 || str[len - 1] == '.')
		return (-1);
	return (1);
}

static int	ft_checknumber_int(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
		i++;
	if (len != i)
		return (-1);
	return (1);
}

int	ft_atoi(char *str, int *result)
{
	int			i;
	int			sign;
	long int	nbr;

	if (ft_checknumber_int(str) == -1)
		return (-1);
	i = 0;
	sign = 1;
	nbr = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nbr = (nbr * 10) + (str[i] - '0');
		if ((nbr * sign) > 2147483647 || (nbr * sign) < -2147483648)
			return (-1);
		i++;
	}
	*result = nbr * sign;
	return (0);
}

int	ft_atof(char *str, float *result)
{
	size_t	i;
	float	divisor;

	if (ft_checknumber_float(str) == -1)
		return (-1);
	i = 0;
	divisor = 10;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (i < ft_strlen(str) && str[i] != '.')
	{
		*result = (*result * 10) + (str[i] - '0');
		i++;
	}
	i++;
	while (i < ft_strlen(str))
	{
		*result = *result + ((str[i] - '0') / divisor);
		divisor *= 10;
		i++;
	}
	if (str[0] == '-')
		*result *= -1;
	return (0);
}
