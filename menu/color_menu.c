/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:35:03 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 16:42:33 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_color	get_color(t_all_data *t)
{
	t_color	result;
	int		i;

	i = t->obj.index;
	if (t->menu.cur_menu == 'a')
		result = t->edit_scene.ambl.c;
	else if (t->menu.cur_menu == 's')
		result = t->edit_scene.sp[i].c;
	else if (t->menu.cur_menu == 'p')
		result = t->edit_scene.pl[i].c;
	else if (t->menu.cur_menu == 'c')
		result = t->edit_scene.cy[i].c;
	return (result);
}

void	apply_color(t_all_data *t)
{
	int	i;

	i = t->obj.index;
	if (t->menu.cur_menu == 'a')
		t->edit_scene.ambl.c = t->menu.color;
	else if (t->menu.cur_menu == 's')
		t->edit_scene.sp[i].c = t->menu.color;
	else if (t->menu.cur_menu == 'p')
		t->edit_scene.pl[i].c = t->menu.color;
	else if (t->menu.cur_menu == 'c')
		t->edit_scene.cy[i].c = t->menu.color;
	printf("Changes applied.\n");
}

static void	change_color(t_all_data *t, char c, int keysym)
{
	float	color;
	int		sign;

	if (c != 'r' && c != 'g' && c != 'b')
	{
		printf("Select a color you want to change first.\n");
		return ;
	}
	sign = 1;
	color = t->menu.color.r;
	if (keysym == 65364)
		sign = -1;
	if (t->menu.color_type == 'g')
		color = t->menu.color.g;
	else if (t->menu.color_type == 'b')
		color = t->menu.color.b;
	if (color + sign >= 0 && color + sign <= 255)
	{
		if (t->menu.color_type == 'r')
			t->menu.color.r += sign;
		else if (t->menu.color_type == 'g')
			t->menu.color.g += sign;
		else if (t->menu.color_type == 'b')
			t->menu.color.b += sign;
	}
}

int	color_hooks(int keysym, t_all_data *t)
{
	if (keysym == 65307)
	{
		system("clear");
		printf("---------EXITING COLOR MENU------------\n\n");
		ft_mainmenu(t);
	}
	if (keysym == 82 || keysym == 114)
		t->menu.color_type = 'r';
	else if ((keysym == 71 || keysym == 103))
		t->menu.color_type = 'g';
	else if ((keysym == 66 || keysym == 98))
		t->menu.color_type = 'b';
	if (keysym == 65362 || keysym == 65364)
	{
		change_color(t, t->menu.color_type, keysym);
		printf("NEW VALUE IF APPLIED: R:%d", t->menu.color.r);
		printf("  G:%d  B:%d\n", t->menu.color.g, t->menu.color.b);
	}
	if (keysym == 65293)
	{
		apply_color(t);
		ft_colormenu(t);
	}
	return (0);
}

void	ft_colormenu(t_all_data *t)
{
	mlx_hook(t->window.win, 2, 1L << 0, color_hooks, t);
	t->menu.color = get_color(t);
	t->menu.color_type = '\0';
	printf("---------ENTERING COLOR MENU------------\n\n");
	printf("Press r to change r value of the color.\n");
	printf("Press g to change g value of the color.\n");
	printf("Press b to change b value of the color.\n");
	printf("Press Enter to apply these changes\n");
	printf("ESC to exit color menu.\n");
	printf("CURRENT COLOR: R:%d", t->menu.color.r);
	printf("  G:%d  B:%d\n", t->menu.color.g, t->menu.color.b);
}
