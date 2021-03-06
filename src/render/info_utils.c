/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <mtupikov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 23:35:00 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/29 23:35:00 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt_v_1.h"

void	put_plane_info(t_sdl *sdl)
{
	char *ut;

	put_info(sdl, R_F, "PLANE", (cl_int3){1285, 10, 15});
	ut = get_char_util("Normal = (", sdl->in.object->normal);
	put_info(sdl, R_F, ut, (cl_int3){1285, 40, 15});
	ft_strdel(&ut);
	ut = get_char_util("Start = (", sdl->in.object->start_point);
	put_info(sdl, R_F, ut, (cl_int3){1285, 70, 15});
	ft_strdel(&ut);
	ut = get_char_util_i("Color = (", sdl->in.object->color);
	put_info(sdl, R_F, ut, (cl_int3){1285, 100, 15});
	ft_strdel(&ut);
	ut = get_num("Specular = ", sdl->in.object->specular);
	put_info(sdl, R_F, ut, (cl_int3){1285, 130, 15});
	ft_strdel(&ut);
}

void	put_cone_info(t_sdl *sdl)
{
	char *ut;

	put_info(sdl, R_F, "CONE", (cl_int3){1285, 10, 15});
	ut = get_char_util("Normal = (", sdl->in.object->normal);
	put_info(sdl, R_F, ut, (cl_int3){1285, 40, 15});
	ft_strdel(&ut);
	ut = get_char_util("Start = (", sdl->in.object->start_point);
	put_info(sdl, R_F, ut, (cl_int3){1285, 70, 15});
	ft_strdel(&ut);
	ut = get_char_util_i("Color = (", sdl->in.object->color);
	put_info(sdl, R_F, ut, (cl_int3){1285, 100, 15});
	ft_strdel(&ut);
	ut = get_num("Specular = ", sdl->in.object->specular);
	put_info(sdl, R_F, ut, (cl_int3){1285, 130, 15});
	ft_strdel(&ut);
	ut = get_num("Height = ", sdl->in.object->height);
	put_info(sdl, R_F, ut, (cl_int3){1285, 160, 15});
	ft_strdel(&ut);
	ut = get_num("Radius = ", sdl->in.object->radius);
	put_info(sdl, R_F, ut, (cl_int3){1285, 190, 15});
	ft_strdel(&ut);
}

void	put_cylinder_info(t_sdl *sdl)
{
	char *ut;

	put_info(sdl, R_F, "CYLINDER", (cl_int3){1285, 10, 15});
	ut = get_char_util("Normal = (", sdl->in.object->normal);
	put_info(sdl, R_F, ut, (cl_int3){1285, 40, 15});
	ft_strdel(&ut);
	ut = get_char_util("Start = (", sdl->in.object->start_point);
	put_info(sdl, R_F, ut, (cl_int3){1285, 70, 15});
	ft_strdel(&ut);
	ut = get_char_util_i("Color = (", sdl->in.object->color);
	put_info(sdl, R_F, ut, (cl_int3){1285, 100, 15});
	ft_strdel(&ut);
	ut = get_num("Specular = ", sdl->in.object->specular);
	put_info(sdl, R_F, ut, (cl_int3){1285, 130, 15});
	ft_strdel(&ut);
	ut = get_num("Radius = ", sdl->in.object->radius);
	put_info(sdl, R_F, ut, (cl_int3){1285, 160, 15});
	ft_strdel(&ut);
}

void	put_sphere_info(t_sdl *sdl)
{
	char *ut;

	put_info(sdl, R_F, "SPHERE", (cl_int3){1285, 10, 15});
	ut = get_char_util("Normal = (", sdl->in.object->normal);
	put_info(sdl, R_F, ut, (cl_int3){1285, 40, 15});
	ft_strdel(&ut);
	ut = get_char_util("Start = (", sdl->in.object->start_point);
	put_info(sdl, R_F, ut, (cl_int3){1285, 70, 15});
	ft_strdel(&ut);
	ut = get_char_util_i("Color = (", sdl->in.object->color);
	put_info(sdl, R_F, ut, (cl_int3){1285, 100, 15});
	ft_strdel(&ut);
	ut = get_num("Specular = ", sdl->in.object->specular);
	put_info(sdl, R_F, ut, (cl_int3){1285, 130, 15});
	ft_strdel(&ut);
	ut = get_num("Radius = ", sdl->in.object->radius);
	put_info(sdl, R_F, ut, (cl_int3){1285, 160, 15});
	ft_strdel(&ut);
}

void	type_object(t_sdl *sdl)
{
	if (sdl->in.object->type == OBJ_PLANE)
		put_plane_info(sdl);
	else if (sdl->in.object->type == OBJ_CONE)
		put_cone_info(sdl);
	else if (sdl->in.object->type == OBJ_CYLINDER)
		put_cylinder_info(sdl);
	else if (sdl->in.object->type == OBJ_SPHERE)
		put_sphere_info(sdl);
}
