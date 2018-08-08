/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_v_1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 13:33:51 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/30 13:34:58 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_V_1_H
# define RT_V_1_H

/*
**	INCLUDES
*/

# include <SDL2/SDL.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include <OpenCL/opencl.h>
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"
# include <math.h>

/*
**	DEFINES
*/

# define SCREEN_WIDTH		1080
# define SCREEN_HEIGHT		1080
# define SCREEN_OFFSET		200
# define MEM_SIZE 			1024
# define INF				10000
# define MAX_SOURCE_SIZE	0x100000
# define G_F				"fonts/Reey-Regular.otf"
# define R_F				"fonts/KronaOne-Regular.ttf"

/*
**	ENUMS
*/

enum					e_obj_type
{
	OBJ_PLANE,
	OBJ_SPHERE,
	OBJ_CYLINDER,
	OBJ_CONE
};

enum					e_light_type
{
	LGT_POINT,
	LGT_AMBIENT,
	LGT_DIRECTIONAL
};

/*
**	STRUCTS
*/

typedef struct			s_roots
{
	float				t1;
	float				t2;
}						t_roots;

typedef struct			s_object_3d
{
	int					height;
	int					type;
	int					specular;
	float				angle;
	float				reflective;
	float				radius;
	cl_int3				color;
	cl_float3			start_point;
	cl_float3			normal;
	cl_float3			rot;
}						t_object_3d;

typedef struct			s_light
{
	int					type;
	float				intensity;
	cl_int3				color;
	cl_float3			start_point;
}						t_light;

typedef struct			s_camera
{
	int					anti_aliasing;
	cl_float3			pos;
	cl_float3			rotation;
}						t_camera;

typedef struct			s_inter
{
	float				closest_t;
	t_object_3d			*object;
}						t_inter;

typedef struct			s_cl
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_platform_id		platform_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				ret;
	cl_mem				lgt;
	cl_mem				obj;
	cl_mem				col;
}						t_cl;

typedef struct			s_rt
{
	int					count_objects;
	int					count_lights;
	t_camera			camera;
}						t_rt;

typedef struct			s_sdl
{
	int					quit;
	SDL_Window			*window;
	SDL_Surface			*screen;
	SDL_Surface			*text;
	TTF_Font			*font;
	SDL_Event			event;
	t_object_3d			*objects;
	t_light				*lights;
	t_rt				rt;
	t_cl				cl;
	t_inter				in;
}						t_sdl;

/*
**	PROTOTYPES
*/

/*
**	main_utils.c
*/

void					rotation_manager(t_sdl *sdl);
void					movement_manager(t_sdl *sdl);
void					error(char *line);

/*
**	sdl_init.c
*/

int						init_sdl(t_sdl *sdl);
int						init_window(t_sdl *sdl);
int						init_renderer(t_sdl *sdl);

/*
**	scene_parser.c
*/

int						scene_parser(t_sdl *sdl, char *file);

/*
**	parse_utils_1.c
*/

int						is_closing_brace(char *str);
int						check_double(char *c);
int						check_num(char *c);
int						get_color(cl_int r, cl_int g, cl_int b);
cl_float3				parse_start_point(char *line);

/*
**	parse_utils_2.c
*/

int						parse_int(char *line);
float					parse_float(char *line, int lim);
cl_int3					parse_color(char *line);
char					*check_equals(char *line);
char					*check_scope(char *line);

/*
**	parse_utils_3.c
*/

cl_float3				parse_rotation(char *line);
cl_float3				add_rotation(float a, float b, float g);
t_object_3d				default_object(void);
t_camera				default_camera(void);
t_light					default_light(void);

/*
**	parse_utils_4.c
*/

void					parse_plane(t_sdl *sdl, int fd);
void					parse_sphere(t_sdl *sdl, int fd);
void					parse_cylinder(t_sdl *sdl, int fd);
void					parse_cone(t_sdl *sdl, int fd);

/*
**	parse_utils_5.c
*/

void					parse_light(t_sdl *sdl, int fd);

/*
**	render.c
*/

void					put_image(t_sdl *sdl);

/*
**	put_info_util.c
*/

void					put_controls(t_sdl *sdl);
void					where_am_i(t_sdl *sdl);
char					*get_char_util_i(char *info, cl_int3 pos);
char					*get_char_util(char *info, cl_float3 pos);
char					*get_num(char *info, int num);

/*
**	put_object_info.c
*/

void					put_plane_info(t_sdl *sdl);
void					put_cone_info(t_sdl *sdl);
void					put_cylinder_info(t_sdl *sdl);
void					put_sphere_info(t_sdl *sdl);

/*
**	vector_stuff.c
*/

float					f_dot(cl_float3 t1, cl_float3 t2);
cl_float3				subtract_3d_vector(cl_float3 t1, cl_float3 t2);

/*
**	closest_stuff.c
*/

t_inter					closest_inter(t_sdl *sdl, cl_float3 o,
						cl_float3 point);

/*
**	closest_stuff_util.c
*/

void					intersect_cone_util(t_object_3d cone, cl_float3	oc,
						cl_float3 point, t_roots *ks);
void					intersect_cylinder_util(t_object_3d cylinder,
						cl_float3	oc, cl_float3 point, t_roots *ks);
void					closest_inter_util(t_sdl *sdl, t_roots ks,
						cl_float3 mm, t_inter *inter);

/*
**	rotate_stuff.c
*/

cl_float3				rotate(cl_float3 t, cl_float3 rotation);

/*
**	sdl_utils.c
*/

void					put_info(t_sdl *sdl, char *font, char *text,
						cl_int3 k);
cl_mem					create_cl_buffer(t_sdl *sdl, size_t size,
						cl_mem_flags flag, void *o);

#endif
