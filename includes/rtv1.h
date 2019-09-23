/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 15:26:15 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/17 15:24:30 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <mlx.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include <math.h>
# include "rtmath.h"

# define KEY_A 0
# define KEY_B 11
# define KEY_C 8
# define KEY_D 2
# define KEY_E 14
# define KEY_F 3
# define KEY_G 5
# define KEY_H 4
# define KEY_I 34
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_M 46
# define KEY_N 45
# define KEY_O 31
# define KEY_P 35
# define KEY_Q 12
# define KEY_R 15
# define KEY_S 1
# define KEY_T 17
# define KEY_U 32
# define KEY_V 9
# define KEY_W 13
# define KEY_X 7
# define KEY_Y 16
# define KEY_Z 6
# define KEY_ZERO 29
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_FIVE 23
# define KEY_SIX 22
# define KEY_SEVEN 26
# define KEY_EIGHT 28
# define KEY_NINE 25
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_MULTI 67
# define KEY_SPACE 49
# define KEY_ENTER 36
# define KEY_ESC 53
# define KEY_TAB 48

# define BACKGROUND 0x303841
# define WIDTH 1920
# define HEIGHT 1080

typedef int		t_bool;
# define TRUE	1
# define FALSE	0

typedef union	u_color
{
	unsigned char	bgra[4];
	int				color;
}				t_color;

typedef struct	s_image
{
	void		*ptr;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_image;

typedef enum	e_objs
{
	none,
	sphere,
	plane,
	cone,
	cylinder,
	light,
	camera
}				t_obj_type;

typedef enum	e_eqparams
{
	a, b, c, d
}				t_eqparams;

typedef struct	s_material
{
	t_color		diff_color;
	float		kd;
	float		ks;
	float		n;
}				t_material;

typedef struct	s_light_source
{
	t_vec4		origin;
	float		intensity;
	t_vec4		c_s;
}				t_light_source;

typedef struct	s_obj
{
	t_obj_type	type;
	t_vec4		c_s;
	t_vec4		origin;
	t_vec4		hit_point;
	t_vec4		surf_normal;
	t_material	mat;
	float		t;
	void		*data;
}				t_obj;

typedef struct	s_ray
{
	t_vec4		point;
	t_vec4		vec;
}				t_ray;

typedef struct	s_sphere
{
	float		radius;
	float		radius2;
}				t_sphere;

typedef struct	s_plane
{
	t_vec4		nv;
}				t_plane;

typedef struct	s_cone
{
	t_vec3		dir;
	float		angle;
	float		k;
	float		k2;
}				t_cone;

typedef struct	s_cylinder
{
	t_vec4		dir;
	float		radius;
}				t_cylinder;

typedef	struct	s_world
{
	t_obj			*objs;
	int				nobjs;
	t_light_source	*lights;
	int				nlights;
}				t_world;

typedef struct	s_camera
{
	t_vec4		origin;
	t_vec4		orient;
	t_mat4		inv_rot;
	int			fov;
	float		near_z;
	float		far_z;
	float		inv_w;
	float		inv_h;
	float		ratio;
	float		angle;
}				t_camera;

typedef struct	s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		img;
	t_world		world;
	t_camera	camera;
	t_obj		*cntrld_obj;
	int			fd;
}				t_param;

void			render(t_param *p);
t_color			trace_ray(t_param *p, t_ray *ray);
t_obj			*get_intersection(t_obj *objs, int nobjs, t_ray *ray);
t_bool			sphere_intersection(t_obj *obj, t_ray *ray);
t_bool			cylinder_intersection(t_obj *obj, t_ray *ray);
t_bool			plane_intersection(t_obj *obj, t_ray *ray);
t_bool			cone_intersection(t_obj *obj, t_ray *ray);
t_color			get_point_color(t_world *world, t_obj *obj, t_ray *ray, int i);
t_ray			cast_shadow_ray(t_vec3 start, t_light_source *light);
void			get_sphere_normal(t_obj *obj);
void			get_plane_normal(t_obj *obj);
void			get_cone_normal(t_obj *obj);
void			get_cylinder_normal(t_obj *obj);
void			get_surface_normal(t_obj *obj);

int				mouse_press(int button, int x, int y, void *param);
int				key_press(int keycode, void *param);

void			world_to_camera(t_param *p);
void			rotate_camera(t_param *p);
void			move_obj_to_camera(t_obj *obj, t_camera *camera);

void			init_sphere(t_list *t, t_obj *p);
void			init_plane(t_list *t, t_obj *p);
void			init_cone(t_list *t, t_obj *p);
void			init_cylinder(t_list *t, t_obj *p);
void			init_light(t_list *t, t_light_source *light);
void			init_camera(t_list *t, t_camera *camera);

void			set_default_camera(t_camera *camera);
int				read_all(int fd, t_param *p);
void			read_vec3_param(char *str, t_vec3 v3param,
				char *param, t_vec3 v3def);
float			read_fparam(char *str, char *param, float dfval);
void			parse_obj(t_list *l, t_param *p, t_obj_type t);
t_material		read_material(t_color dcolor);

int				parse_list(t_param *p, t_list *l);
size_t			list_len(t_list *l, t_param *p);
void			delete_lst(void *s, size_t size);

t_obj_type		find_type(t_list *l);
char			*str_to_low(char *str);
void			convert_to16(int val, char *num, char *ax);
char			*ft_itoaf(float val, int fdigits);

void			file_save(t_param *p);
void			print_fnumber(float val, int fd, int fdigits);
void			out_fparam(float val, char *param, int fd);
void			out_v3_param(t_vec3 val, char *param, int fd);
void			out_plane(t_obj obj, int fd);
void			out_sphere(t_obj obj, int fd);
void			out_cone(t_obj obj, int fd);
void			out_cylinder(t_obj obj, int fd);
void			out_camera(t_camera cam, int fd);
void			output_obj(t_obj obj, int fd);
void			output_light(t_light_source l, int fd);
void			output_data(t_param *p);

#endif
