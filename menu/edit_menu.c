/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 03:58:46 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 16:39:57 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	get_value(t_all_data *t)
{
	int	i;

	i = t->obj.index;
	if (ft_strncmp(t->menu.toedit, "fov", 3) == 0)
		t->menu.value_i = t->edit_scene.cam.fov;
	else if (ft_strncmp(t->menu.toedit, "brightness", 10) == 0)
		t->menu.value_f = t->edit_scene.light.bright;
	else if (ft_strncmp(t->menu.toedit, "ambient", 7) == 0)
		t->menu.value_f = t->edit_scene.ambl.ambl_r;
	else if (ft_strncmp(t->menu.toedit, "sp_dia", 6) == 0)
		t->menu.value_f = t->edit_scene.sp[i].dia;
	else if (ft_strncmp(t->menu.toedit, "cy_dia", 6) == 0)
		t->menu.value_f = t->edit_scene.cy[i].dia;
	else if (ft_strncmp(t->menu.toedit, "cy_height", 9) == 0)
		t->menu.value_f = t->edit_scene.cy[i].height;
}

void	apply_value(t_all_data *t)
{
	int	i;

	i = t->obj.index;
	if (ft_strncmp(t->menu.toedit, "fov", 3) == 0)
		t->edit_scene.cam.fov = t->menu.value_i;
	else if (ft_strncmp(t->menu.toedit, "brightness", 10) == 0)
		t->edit_scene.light.bright = t->menu.value_f;
	else if (ft_strncmp(t->menu.toedit, "ambient", 7) == 0)
		t->edit_scene.ambl.ambl_r = t->menu.value_f;
	else if (ft_strncmp(t->menu.toedit, "sp_dia", 6) == 0)
		t->edit_scene.sp[i].dia = t->menu.value_f;
	else if (ft_strncmp(t->menu.toedit, "cy_dia", 6) == 0)
		t->edit_scene.cy[i].dia = t->menu.value_f;
	else if (ft_strncmp(t->menu.toedit, "cy_height", 9) == 0)
		t->edit_scene.cy[i].height = t->menu.value_f;
	printf("Changes applied.\n");
	ft_mainmenu(t);
}

int	change_edit_hooks(int keysym, t_all_data *t)
{
	int	i;

	if (keysym == 65307)
	{
		i = 0;
		while (i < 20)
		{
			t->menu.toedit[i] = '\0';
			i++;
		}
		system("clear");
		printf("---------EXITED EDIT MENU------------\n\n");
		ft_mainmenu(t);
	}
	if (keysym == 65362)
		to_increase(t);
	if (keysym == 65364)
		to_decrease(t);
	if (keysym == 65293)
		apply_value(t);
	return (0);
}

void	ft_editmenu(t_all_data *t)
{
	mlx_hook(t->window.win, 2, 1L << 0, change_edit_hooks, t);
	get_value(t);
	printf("------------ENTERING EDIT MENU------------\n\n");
	printf("1.Press UP button to increase the value.\n");
	printf("2.Press DOWN button to decrease the value.\n");
	printf("3.Press ENTER to apply the value change.\n");
	printf("4.Press ESC to exit the edit menu.\n");
	if (ft_strncmp(t->menu.toedit, "fov", 3) == 0)
		printf("CURRENT FOV: %d\n", t->menu.value_i);
	else if (ft_strncmp(t->menu.toedit, "brightness", 10) == 0)
		printf("CURRENT BRIGHTNESS: %f\n", t->menu.value_f);
	else if (ft_strncmp(t->menu.toedit, "ambient", 7) == 0)
		printf("CURRENT AMBIENT: %f\n", t->menu.value_f);
	else if (ft_strncmp(t->menu.toedit, "sp_dia", 6) == 0)
		printf("CURRENT SPHERE DIAMETER: %f\n", t->menu.value_f);
	else if (ft_strncmp(t->menu.toedit, "cy_dia", 6) == 0)
		printf("CURRENT CYLINDER DIAMETER: %f\n", t->menu.value_f);
	else if (ft_strncmp(t->menu.toedit, "cy_height", 9) == 0)
		printf("CURRENT CYLINDER HEIGHT: %f\n", t->menu.value_f);
}
