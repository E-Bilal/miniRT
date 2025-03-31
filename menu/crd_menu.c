/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crd_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:21:21 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 16:33:37 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static t_crd	get_crd(t_all_data *t)
{
	int		i;
	t_crd	result;

	i = t->obj.index;
	if (t->menu.cur_menu == 'k')
		result = t->edit_scene.cam.crd;
	else if (t->menu.cur_menu == 'l')
		result = t->edit_scene.light.crd;
	else if (t->menu.cur_menu == 'p')
		result = t->edit_scene.pl[i].crd;
	else if (t->menu.cur_menu == 's')
		result = t->edit_scene.sp[i].crd;
	else if (t->menu.cur_menu == 'c')
		result = t->edit_scene.cy[i].crd;
	return (result);
}

static void	apply_crd(t_all_data *t)
{
	int	i;

	i = t->obj.index;
	if (t->menu.cur_menu == 'k')
	{
		t->edit_scene.cam.crd = t->menu.crd;
		ft_offsetcam_crd(&t->edit_scene);
	}
	else if (t->menu.cur_menu == 'l')
		t->edit_scene.light.crd = t->menu.crd;
	else if (t->menu.cur_menu == 'p')
		t->edit_scene.pl[i].crd = t->menu.crd;
	else if (t->menu.cur_menu == 's')
		t->edit_scene.sp[i].crd = t->menu.crd;
	else if (t->menu.cur_menu == 'c')
		t->edit_scene.cy[i].crd = t->menu.crd;
	printf("Changes applied.\n");
}

static void	change_crd(t_all_data *t, char c, int keysym)
{
	float	crd;
	int		sign;

	if (c != 'x' && c != 'y' && c != 'z')
	{
		printf("Select a crd you want to change first.\n");
		return ;
	}
	sign = 1;
	crd = t->menu.crd.x;
	if (keysym == 65364)
		sign = -1;
	if (t->menu.crd_type == 'y')
		crd = t->menu.crd.y;
	else if (t->menu.crd_type == 'z')
		crd = t->menu.crd.z;
	if (crd + sign >= -1000 && crd + sign <= 1000)
	{
		if (t->menu.crd_type == 'x')
			t->menu.crd.x += sign;
		else if (t->menu.crd_type == 'y')
			t->menu.crd.y += sign;
		else if (t->menu.crd_type == 'z')
			t->menu.crd.z += sign;
	}
}

static int	crd_hooks(int keysym, t_all_data *t)
{
	if (keysym == 65307)
	{
		system("clear");
		printf("---------EXITING CRD MENU------------\n\n");
		ft_mainmenu(t);
	}
	if (keysym == 88 || keysym == 120)
		t->menu.crd_type = 'x';
	else if (keysym == 89 || keysym == 121)
		t->menu.crd_type = 'y';
	else if ((keysym == 90 || keysym == 122))
		t->menu.crd_type = 'z';
	if (keysym == 65362 || keysym == 65364)
	{
		change_crd(t, t->menu.crd_type, keysym);
		printf("NEW VALUE IF APPLIED: X:%f", t->menu.crd.x);
		printf("  Y:%f  Z:%f\n", t->menu.crd.y, t->menu.crd.z);
	}
	if (keysym == 65293)
	{
		apply_crd(t);
		ft_crdmenu(t);
	}
	return (0);
}

void	ft_crdmenu(t_all_data *t)
{
	mlx_hook(t->window.win, 2, 1L << 0, crd_hooks, t);
	t->menu.crd = get_crd(t);
	t->menu.crd_type = '\0';
	printf("---------ENTERING CRD MENU------------\n\n");
	printf("Press x to change X coordinate.\n");
	printf("Press y to change Y coordinate.\n");
	printf("Press z to change Z coordinate.\n");
	printf("Press Enter to apply these changes\n");
	printf("ESC to exit crd menu.\n");
	printf("CURRENT CRD: X:%f", t->menu.crd.x);
	printf("  Y:%f  Z:%f\n", t->menu.crd.y, t->menu.crd.z);
}
