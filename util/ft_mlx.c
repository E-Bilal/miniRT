/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:48:55 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 10:22:14 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	get_screensize(t_mlxwindow *window, t_viewport *vp)
{
	vp->res_x = 0;
	vp->res_y = 0;
	window->mlx = mlx_init();
	if (window->mlx == NULL)
		exit(EXIT_FAILURE);
	mlx_get_screen_size(window->mlx, &vp->res_x, &vp->res_y);
	mlx_destroy_display(window->mlx);
	free (window->mlx);
	vp->res_x = vp->res_x - ((float)vp->res_x / 4);
	vp->res_y = (vp->res_x / 16) * 9;
}

void	ft_initwindow(t_mlxwindow *window, t_viewport vp, t_img *img)
{
	window->mlx = mlx_init();
	if (window->mlx == NULL)
	{
		exit(EXIT_FAILURE);
	}
	window->win = mlx_new_window(window->mlx, vp.res_x, vp.res_y, "miniRT");
	if (window->win == NULL)
	{
		mlx_destroy_display(window->mlx);
		free (window->mlx);
		exit(EXIT_FAILURE);
	}
	window->image = mlx_new_image(window->mlx, vp.res_x, vp.res_y);
	if (window->image == NULL)
	{
		mlx_destroy_window(window->mlx, window->win);
		mlx_destroy_display(window->mlx);
		free (window->mlx);
		exit(EXIT_FAILURE);
	}
	img->addr = mlx_get_data_addr(window->image, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	ft_initimage_redraw(t_mlxwindow *window, t_viewport vp)
{
	mlx_destroy_image(window->mlx, window->image);
	window->image = mlx_new_image(window->mlx, vp.res_x, vp.res_y);
	if (window->image == NULL)
	{
		mlx_destroy_window(window->mlx, window->win);
		mlx_destroy_display(window->mlx);
		free (window->mlx);
		exit(EXIT_FAILURE);
	}
}

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
