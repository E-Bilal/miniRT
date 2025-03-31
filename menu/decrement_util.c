/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decrement_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:02:36 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 16:47:26 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	dec_dimension(t_all_data *t)
{
	float	dimension;

	dimension = t->menu.value_f;
	if (dimension - 1 > 0)
		t->menu.value_f -= 1;
	printf("NEW DIMENSION IF APPLIED: %f\n", t->menu.value_f);
}

void	dec_fov(t_all_data *t)
{
	int	fov;

	fov = t->menu.value_i;
	if (fov - 1 >= 0)
		fov -= 1;
	t->menu.value_i = fov;
	printf("NEW FOV IF APPLIED: %d\n", t->menu.value_i);
}

void	dec_bright_ambient(t_all_data *t)
{
	float	bright_amb;

	bright_amb = t->menu.value_f;
	if (bright_amb - 0.1 >= 0)
		bright_amb -= 0.1;
	t->menu.value_f = bright_amb;
	if (ft_strncmp(t->menu.toedit, "brightness", 10) == 0)
		printf("NEW BRIGHTNESS IF APPLIED: %f\n", t->menu.value_f);
	if (ft_strncmp(t->menu.toedit, "ambient", 7) == 0)
		printf("NEW AMBIENT IF APPLIED: %f\n", t->menu.value_f);
}

void	to_decrease(t_all_data *t)
{
	if (ft_strncmp(t->menu.toedit, "fov", 3) == 0)
		dec_fov(t);
	else if (ft_strncmp(t->menu.toedit, "brightness", 10) == 0)
		dec_bright_ambient(t);
	else if (ft_strncmp(t->menu.toedit, "ambient", 7) == 0)
		dec_bright_ambient(t);
	else if (ft_strncmp(t->menu.toedit, "sp_dia", 6) == 0)
		dec_dimension(t);
	else if (ft_strncmp(t->menu.toedit, "cy_dia", 6) == 0)
		dec_dimension(t);
	else if (ft_strncmp(t->menu.toedit, "cy_height", 6) == 0)
		dec_dimension(t);
}
