/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 23:53:43 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 10:26:56 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	debug_sphere(t_scene scene)
{
	int	i;

	i = 0;
	while (i < scene.sp_index)
	{
		printf("spehre dia: %f\n", scene.sp[i].dia);
		printf("spehre_x: %f\n", scene.sp[i].crd.x);
		printf("sphere_y: %f\n", scene.sp[i].crd.y);
		printf("sphere_z: %f\n", scene.sp[i].crd.z);
		printf("spehrecolor_r: %d\n", scene.sp[i].c.r);
		printf("spehrecolor_g: %d\n", scene.sp[i].c.g);
		printf("spehrecolor_b: %d\n", scene.sp[i].c.b);
		i++;
		printf("-------------------------\n");
	}
}

static void	debug_plane(t_scene scene)
{
	int	i;

	i = 0;
	while (i < scene.pl_index)
	{
		printf("plane_x: %f\n", scene.pl[i].crd.x);
		printf("plane_y: %f\n", scene.pl[i].crd.y);
		printf("plane_z: %f\n", scene.pl[i].crd.z);
		printf("plane_vecx: %f\n", scene.pl[i].v.x);
		printf("plane_vecy: %f\n", scene.pl[i].v.y);
		printf("plane_vecz: %f\n", scene.pl[i].v.z);
		printf("planecolor_r: %d\n", scene.pl[i].c.r);
		printf("planecolor_g: %d\n", scene.pl[i].c.g);
		printf("planecolor_b: %d\n", scene.pl[i].c.b);
		i++;
		printf("-------------------------\n");
	}
}

static void	debug_cylinder(t_scene scene)
{
	int	i;

	i = 0;
	while (i < scene.cy_index)
	{
		printf("Cylinder diameter: %f\n", scene.cy[i].dia);
		printf("Cylinder height: %f\n", scene.cy[i].height);
		printf("Cylinder_x: %f\n", scene.cy[i].crd.x);
		printf("Cylinder_y: %f\n", scene.cy[i].crd.y);
		printf("Cylinder_z: %f\n", scene.cy[i].crd.z);
		printf("Cylindercolor_r: %d\n", scene.cy[i].c.r);
		printf("Cylindercolor_g: %d\n", scene.cy[i].c.g);
		printf("Cylindercolor_b: %d\n", scene.cy[i].c.b);
		i++;
		printf("-------------------------\n");
	}
}

void	debuginfo(t_scene scene)
{
	printf("ambient strength:%f\n", scene.ambl.ambl_r);
	printf("ambientcolor_r:%d\n", scene.ambl.c.r);
	printf("ambientcolor_g:%d\n", scene.ambl.c.g);
	printf("ambientcolor_b:%d\n", scene.ambl.c.b);
	printf("light_x: %f\n", scene.light.crd.x);
	printf("light_y: %f\n", scene.light.crd.y);
	printf("light_z: %f\n", scene.light.crd.z);
	printf("cam_fov: %d\n", scene.cam.fov);
	printf("camvec_x: %f\n", scene.cam.v.x);
	printf("camvec_y: %f\n", scene.cam.v.y);
	printf("camvec_z: %f\n", scene.cam.v.z);
	printf("camx:%f\n", scene.cam.crd.x);
	printf("camy:%f\n", scene.cam.crd.y);
	printf("camz:%f\n", scene.cam.crd.z);
	printf("sphere index:%d\n", scene.sp_index);
	debug_sphere(scene);
	debug_plane(scene);
	debug_cylinder(scene);
	printf("-------------------------\n");
}
