/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:54:12 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 10:14:29 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char *argv[])
{
	t_all_data	t;

	if (argc != 2)
	{
		write(1, "Error\nOnly 1 argument is allowed\n", 34);
		exit(EXIT_FAILURE);
	}
	ft_initdata(&t);
	ft_parse_file(argv[1], &t.scene);
	ft_offsetcam_crd(&t.scene);
	ft_offsetcam_vec(&t.scene);
	ft_copyscene(&t.edit_scene, &t.scene);
	get_screensize(&t.window, &t.vp);
	ft_initwindow(&t.window, t.vp, &t.img);
	create_viewport(&t.scene, &t.vp);
	send_rays(t.scene, t.vp, &t.img, t.obj);
	print_instruction();
	mlx_put_image_to_window(t.window.mlx, t.window.win, t.window.image, 0, 0);
	ft_main_hooks(&t);
	mlx_loop(t.window.mlx);
}
