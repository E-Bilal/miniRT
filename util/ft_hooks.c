/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:52:26 by senayat           #+#    #+#             */
/*   Updated: 2024/11/25 11:52:27 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	mouse_null(int button, int x, int y, t_all_data *t)
{
	(void)x;
	(void)y;
	(void)button;
	(void)t;
	return (0);
}

int	program_exit(t_all_data *t)
{
	mlx_destroy_image(t->window.mlx, t->window.image);
	mlx_destroy_window(t->window.mlx, t->window.win);
	mlx_destroy_display(t->window.mlx);
	free (t->window.mlx);
	exit(EXIT_SUCCESS);
}

int	mouse_hooks(int button, int x, int y, t_all_data *t)
{
	t_vec	origin;

	(void)button;
	origin = convert_crd_to_vec(t->scene.cam.crd);
	t->obj.type = 'x';
	hit_scene(origin, create_ray(t->scene, t->vp, x, y), t->scene, &t->obj);
	if (t->obj.type == 's')
		t->menu.cur_menu = 's';
	else if (t->obj.type == 'p')
		t->menu.cur_menu = 'p';
	else if (t->obj.type == 'c')
		t->menu.cur_menu = 'c';
	if (t->obj.type == 's' || t->obj.type == 'p' || t->obj.type == 'c')
		ft_mainmenu(t);
	else
		printf("No objects on this pixel.\n");
	return (0);
}

int	keyboard_hooks(int keysym, t_all_data *t)
{
	t->menu.cur_menu = '\0';
	if (keysym == 65307)
		program_exit(t);
	else if (keysym == 99 || keysym == 67)
		t->menu.cur_menu = 'k';
	else if ((keysym == 76 || keysym == 108))
		t->menu.cur_menu = 'l';
	else if ((keysym == 65 || keysym == 97))
		t->menu.cur_menu = 'a';
	else if (keysym == 82 || keysym == 114)
	{
		ft_copyscene(&t->scene, &t->edit_scene);
		ft_initimage_redraw(&t->window, t->vp);
		create_viewport(&t->scene, &t->vp);
		t->img.addr = mlx_get_data_addr(t->window.image, &t->img.bits_per_pixel,
				&t->img.line_length, &t->img.endian);
		send_rays(t->scene, t->vp, &t->img, t->obj);
		mlx_put_image_to_window(t->window.mlx, t->window.win,
			t->window.image, 0, 0);
		print_instruction();
	}
	if (t->menu.cur_menu == 'k' || t->menu.cur_menu == 'l'
		|| t->menu.cur_menu == 'a')
		ft_mainmenu(t);
	return (0);
}

void	ft_main_hooks(t_all_data *t)
{
	mlx_hook(t->window.win, 17, 1L << 2, program_exit, t);
	mlx_hook(t->window.win, 2, 1L << 0, keyboard_hooks, t);
	mlx_hook(t->window.win, 4, 1L << 2, mouse_hooks, t);
}
