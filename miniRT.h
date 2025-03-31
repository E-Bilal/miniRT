/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:58:23 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 12:16:56 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "./get_next_line/get_next_line.h"
# include "./mlx_linux/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>

/* ************************************************************************** */
/*                                   Structs                                  */
/* ************************************************************************** */
typedef struct t_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct t_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;
typedef struct t_crd
{
	float	x;
	float	y;
	float	z;
}	t_crd;
typedef struct t_viewport
{
	int		res_x;
	int		res_y;
	float	viewport_y;
	float	viewport_x;
	t_vec	top_leftpixel;
	t_vec	viewport_vecx;
	t_vec	viewport_vecy;
	t_vec	pixel_delta_x;
	t_vec	pixel_delta_y;
	t_vec	backvector;
	t_vec	upvector;
	t_vec	rightvector;
}	t_viewport;

typedef struct t_menu
{
	char	cur_menu;
	char	toedit[20];
	char	edit_type;
	int		value_i;
	float	value_f;
	char	crd_type;
	char	vec_type;
	char	color_type;
	t_crd	crd;
	t_vec	vec;
	t_color	color;
}	t_menu;

typedef struct t_quat
{
	float	w;
	float	x;
	float	y;
	float	z;
}	t_quat;

typedef struct t_camera
{
	t_vec	v;
	t_crd	crd;
	int		fov;
}	t_camera;

typedef struct t_light
{
	t_crd	crd;
	t_color	c;
	float	bright;
}	t_light;

typedef struct t_ambl
{
	float	ambl_r;
	t_color	c;
}	t_ambl;

typedef struct t_sphere
{
	t_crd	crd;
	t_color	c;
	float	dia;
}	t_sphere;

typedef struct t_plane
{
	t_crd	crd;
	t_color	c;
	t_vec	v;
}	t_plane;

typedef struct t_ray_cy
{
	float	a;
	float	b;
	t_vec	ba;
	float	bard;
	float	baoc;
	float	baba;
	float	body_t1;
	float	body_t2;
	float	cap_t1;
	float	cap_t2;
	float	height1;
	float	height2;
	float	ra;
	float	discriminant;
}	t_ray_cy;

typedef struct t_cylinder
{
	t_crd	crd;
	t_color	c;
	t_vec	v;
	float	dia;
	float	height;
}	t_cylinder;

typedef struct t_hit
{
	int		index;
	int		edgecase_status;
	float	t;
	float	light_angle;
	char	type;
	t_vec	hitpoint;
	t_vec	normal;
}	t_hit;

typedef struct t_scene
{
	t_light		light;
	t_camera	cam;
	t_ambl		ambl;
	int			cam_limit;
	int			amb_limit;
	int			light_limit;
	int			sp_index;
	int			pl_index;
	int			cy_index;
	t_sphere	sp[50];
	t_plane		pl[50];
	t_cylinder	cy[50];
}	t_scene;

typedef struct t_img
{
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct t_mlxwindow
{
	void	*mlx;
	void	*win;
	void	*image;
}	t_mlxwindow;

typedef struct t_all_data
{
	t_scene		scene;
	t_scene		edit_scene;
	t_mlxwindow	window;
	t_img		img;
	t_menu		menu;
	t_viewport	vp;
	t_hit		obj;
}	t_all_data;

/*************************************************************************** */
/*                                 LIBFT                                     */
/*************************************************************************** */
int		ft_strncmp(char const *str1, char const *str2, size_t n);
char	**ft_split(char *s, char c);
size_t	ft_strlen(const char *str);
/*************************************************************************** */
/*                                  Parsing                                  */
/*************************************************************************** */
int		ft_checkextension(char *filename);
void	ft_parse_file(char *filename, t_scene *scene);
int		ft_openfile(char *filename);
int		parse_ambientl(char **arr, t_scene *scene);
int		parse_cam(char **arr, t_scene *scene);
int		parse_light(char **arr, t_scene *scene);
int		parse_sphere(char **arr, t_scene *scene);
int		parse_crd(char **arr, t_crd *crd);
int		parse_vec(char **arr, t_vec *vec);
int		parse_color(char **arr, t_color *color);
int		parse_plane(char **arr, t_scene *scene);
int		parse_cylinder(char **arr, t_scene *scene);
/* ************************************************************************** */
/*                             Hooks and Menus                                */
/* ************************************************************************** */
void	ft_mainmenu(t_all_data *t);
void	print_instruction(void);
void	ft_vecmenu(t_all_data *t);
int		mouse_hooks(int button, int x, int y, t_all_data *t);
int		mouse_null(int button, int x, int y, t_all_data *t);
int		keyboard_hooks(int keysym, t_all_data *t);
void	ft_editmenu(t_all_data *t);
void	ft_offsetcam_crd(t_scene *scene);
void	to_increase(t_all_data *t);
void	to_decrease(t_all_data *t);
void	ft_colormenu(t_all_data *t);
void	ft_crdmenu(t_all_data *t);
/* ************************************************************************** */
/*                                  MLX                                       */
/* ************************************************************************** */
void	draw_pixel(t_img *img, int x, int y, int color);
void	ft_initimage_redraw(t_mlxwindow *window, t_viewport vp);
void	ft_initwindow(t_mlxwindow *window, t_viewport vp, t_img *img);
void	ft_main_hooks(t_all_data *t);
void	get_screensize(t_mlxwindow *window, t_viewport *vp);
/* ************************************************************************** */
/*                          Init structs and data                             */
/* ************************************************************************** */
t_crd	initcrd(float x, float y, float z);
t_vec	initvector(float x, float y, float z);
t_color	initcolor(int r, int g, int b);
void	ft_initdata(t_all_data *t);
void	ft_copyscene(t_scene *dest_scene, t_scene *src_scene);
/* ************************************************************************** */
/*                            Convert to INT                                  */
/* ************************************************************************** */
int		ft_atoi(char *str, int *result);
int		ft_atof(char *str, float *result);
/* ************************************************************************** */
/*               Vector, Coordinates arithmetic and Math Util                 */
/* ************************************************************************** */
t_crd	offsetcrd(t_crd crd, t_crd offset);
t_vec	vecadditon(t_vec v1, t_vec v2);
t_vec	veccrdadditon(t_vec v1, t_crd v2);
t_vec	vecsubtract(t_vec v1, t_vec v2);
t_vec	crdvecsubtract(t_crd crd, t_vec v2);
t_vec	vecrdsubtract(t_vec v, t_crd crd);
t_vec	vecmutiply(float multiplier, t_vec v1);
t_vec	vecdivision(float divisor, t_vec v1);
t_vec	cross(t_vec v1, t_vec v2);
t_vec	normalize(t_vec v1);
t_vec	convert_crd_to_vec(t_crd crd);
float	dot(t_vec v1, t_vec v2);
float	magnitude(t_vec v1);
float	ft_signum(float nbr);
/* ************************************************************************** */
/*                              Quaternion arithmetic                         */
/* ************************************************************************** */
t_quat	create_quaternion(t_vec cur_vec);
t_vec	rotate_vec(t_vec vec, t_quat q);
t_crd	rotate_crd(t_crd crd, t_quat q);
/* ************************************************************************** */
/*                                Raytracing                                  */
/* ************************************************************************** */
void	create_viewport(t_scene *scene, t_viewport *vp);
void	ft_offsetcam_crd(t_scene *scene);
void	ft_offsetcam_vec(t_scene *scene);
t_vec	create_ray(t_scene scene, t_viewport vp, float x, float y);
void	send_rays(t_scene scene, t_viewport vp, t_img *img, t_hit obj);
bool	hit_scene(t_vec origin, t_vec ray, t_scene scene, t_hit *shape);
bool	hit_sphere(t_vec origin, t_vec ray, t_hit *sp, t_sphere sphere);
bool	hit_plane(t_vec origin, t_vec ray, t_hit *shape, t_plane plane);
bool	point_in_plane(t_plane plane, t_crd origin);
bool	light_and_cam_in_plane(t_scene scene);
bool	hit_cylinder(t_vec origin, t_vec ray, t_hit *sp, t_cylinder cylinder);
void	sphere_normal(t_vec origin, t_vec ray, t_hit *obj, t_sphere sp);
void	plane_normal(t_vec origin, t_vec ray, t_hit *obj, t_plane pl);
void	calc_shadowlight(t_vec origin, t_vec ray, t_scene scene, t_hit *obj);
void	calc_shadowlight(t_vec origin, t_vec ray, t_scene scene, t_hit *obj);
int		set_color(t_hit obj, t_scene scene, t_ambl amb, t_light light);
bool	point_in_cylinder(t_vec point, t_cylinder cylinder);
/* ************************************************************************** */
/*                                Debug                                       */
/* ************************************************************************** */
void	debuginfo(t_scene scene);
#endif
