/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mainmenu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 00:22:17 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 16:45:32 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	print_instruction(void)
{
	printf("-------------------INSTRUCTIONS-----------\n\n\n");
	printf("1.Press C to enter camera menu.\n");
	printf("2.Press L to enter light menu.\n");
	printf("3.Press A to enter ambient menu.\n");
	printf("4.Click on an object to enter that object's menu.\n");
	printf("5.Press R to render the scene again.\n");
	printf("6.Press ESC to exit the program\n");
}

static void	object_menu(t_all_data *t, int k, char m)
{
	if (m == 'c' && (k == 82 || k == 114))
	{
		ft_strlcpy(t->menu.toedit, "cy_dia", 6);
		ft_editmenu(t);
	}
	else if (m == 'c' && (k == 72 || k == 104))
	{
		ft_strlcpy(t->menu.toedit, "cy_height", 9);
		ft_editmenu(t);
	}
	else if (m == 's' && (k == 82 || k == 114))
	{
		ft_strlcpy(t->menu.toedit, "sp_dia", 6);
		ft_editmenu(t);
	}
}

static void	value_menu(t_all_data *t, int k, char m)
{
	if (m == 'k' && (k == 70 || k == 102))
	{
		ft_strlcpy(t->menu.toedit, "fov", 3);
		ft_editmenu(t);
	}
	else if (m == 'a' && (k == 66 || k == 98))
	{
		ft_strlcpy(t->menu.toedit, "ambient", 7);
		ft_editmenu(t);
	}
	else if (m == 'l' && (k == 66 || k == 98))
	{
		ft_strlcpy(t->menu.toedit, "brightness", 10);
		ft_editmenu(t);
	}
}

int	mainmenu_hooks(int keysym, t_all_data *t)
{
	int		k;
	char	m;

	k = keysym;
	m = t->menu.cur_menu;
	if (keysym == 65307)
	{
		mlx_hook(t->window.win, 2, 1L << 0, keyboard_hooks, t);
		mlx_hook(t->window.win, 4, 1L << 2, mouse_hooks, t);
		system("clear");
		t->menu.cur_menu = '\0';
		printf("---------EXITING MENU------------\n\n");
		print_instruction();
	}
	else if (m != 'a' && (k == 67 || k == 112))
		ft_crdmenu(t);
	else if ((m == 'p' || m == 'c' || m == 'k') && (k == 86 || k == 118))
		ft_vecmenu(t);
	else if (m != 'k' && (keysym == 99 || keysym == 67))
		ft_colormenu(t);
	object_menu(t, k, m);
	value_menu(t, k, m);
	return (0);
}

void	ft_mainmenu(t_all_data *t)
{
	char	m;

	m = t->menu.cur_menu;
	mlx_hook(t->window.win, 2, 1L << 0, mainmenu_hooks, t);
	mlx_hook(t->window.win, 4, 1L << 2, mouse_null, t);
	system("clear");
	printf("---------ENTERING MENU------------\n\n");
	if (m != 'a')
		printf("P to change position.\n");
	if (m == 'p' || m == 'c' || m == 'k')
		printf("V to change vector.\n");
	if (m != 'k' && m != 'l')
		printf("C to change color.\n");
	if (m == 'a')
		printf("B to change ambient strength.\n");
	if (m == 'k')
		printf("F to change cam FOV.\n");
	if (t->menu.cur_menu == 'l')
		printf("B to change brightness.\n");
	if (m == 's' || m == 'c')
		printf("R to change object diameter.\n");
	if (m == 'c')
		printf("H to change cylinder height.\n");
	printf("ESC to see the instructions.\n");
}
