/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:21:21 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 16:37:34 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec	get_vec(t_all_data *t)
{
	t_vec	result;
	int		i;

	i = t->obj.index;
	if (t->menu.cur_menu == 'k')
		result = t->edit_scene.cam.v;
	else if (t->menu.cur_menu == 'p')
		result = t->edit_scene.pl[i].v;
	else if (t->menu.cur_menu == 'c')
		result = t->edit_scene.cy[i].v;
	return (result);
}

static void	apply_vec(t_all_data *t)
{
	int	i;

	i = t->obj.index;
	if (t->menu.cur_menu == 'k')
	{
		t->edit_scene.cam.v = t->menu.vec;
		ft_offsetcam_vec(&t->edit_scene);
	}
	else if (t->menu.cur_menu == 'p')
		t->edit_scene.pl[i].v = t->menu.vec;
	else if (t->menu.cur_menu == 'c')
		t->edit_scene.cy[i].v = t->menu.vec;
}

static void	change_vec(t_all_data *t, char c, int keysym)
{
	float	sign;

	if (c != 'x' && c != 'y' && c != 'z')
	{
		printf("Select a vec you want to change first.\n");
		return ;
	}
	sign = 0.1;
	if (keysym == 65364)
		sign = -0.1;
	if (t->menu.vec_type == 'x')
		t->menu.vec.x += sign;
	else if (t->menu.vec_type == 'y')
		t->menu.vec.y += sign;
	else if (t->menu.vec_type == 'z')
		t->menu.vec.z += sign;
	t->menu.vec = normalize(t->menu.vec);
}

static int	vec_hooks(int keysym, t_all_data *t)
{
	if (keysym == 65307)
	{
		system("clear");
		printf("---------EXITING VEC MENU------------\n\n");
		ft_mainmenu(t);
	}
	if (keysym == 88 || keysym == 120)
		t->menu.vec_type = 'x';
	else if (keysym == 89 || keysym == 121)
		t->menu.vec_type = 'y';
	else if ((keysym == 90 || keysym == 122))
		t->menu.vec_type = 'z';
	if (keysym == 65362 || keysym == 65364)
	{
		change_vec(t, t->menu.vec_type, keysym);
		printf("NEW VALUE IF APPLIED: X:%f", t->menu.vec.x);
		printf("  Y:%f  Z:%f\n", t->menu.vec.y, t->menu.vec.z);
	}
	if (keysym == 65293)
	{
		apply_vec(t);
		ft_vecmenu(t);
	}
	return (0);
}

void	ft_vecmenu(t_all_data *t)
{
	mlx_hook(t->window.win, 2, 1L << 0, vec_hooks, t);
	t->menu.vec = get_vec(t);
	t->menu.vec_type = '\0';
	printf("---------ENTERING VEC MENU------------\n\n");
	printf("Press x to change X vector.\n");
	printf("Press y to change Y vector.\n");
	printf("Press z to change Z vector.\n");
	printf("Press Enter to apply these changes\n");
	printf("ESC to exit vec menu.\n");
	printf("CURRENT VEC: X:%f", t->menu.vec.x);
	printf("  Y:%f  Z:%f\n", t->menu.vec.y, t->menu.vec.z);
}
