/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_info_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <mtupikov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 12:31:00 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/30 12:31:00 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt_v_1.h"

char	*get_char_util(char *info, cl_float3 pos)
{
	char *x;
	char *y;
	char *z;
	char *temp;

	x = ft_itoa((int)pos.x);
	y = ft_itoa((int)pos.y);
	z = ft_itoa((int)pos.z);
	info = ft_strjoin(info, x);
	temp = ft_strjoin(info, ", ");
	ft_strdel(&info);
	info = ft_strjoin(temp, y);
	ft_strdel(&temp);
	temp = ft_strjoin(info, ", ");
	ft_strdel(&info);
	info = ft_strjoin(temp, z);
	ft_strdel(&temp);
	temp = ft_strjoin(info, ")");
	ft_strdel(&info);
	ft_strdel(&x);
	ft_strdel(&y);
	ft_strdel(&z);
	return (temp);
}

char	*get_char_util_i(char *info, cl_int3 pos)
{
	char *x;
	char *y;
	char *z;
	char *temp;

	x = ft_itoa(pos.x);
	y = ft_itoa(pos.y);
	z = ft_itoa(pos.z);
	info = ft_strjoin(info, x);
	temp = ft_strjoin(info, ", ");
	ft_strdel(&info);
	info = ft_strjoin(temp, y);
	ft_strdel(&temp);
	temp = ft_strjoin(info, ", ");
	ft_strdel(&info);
	info = ft_strjoin(temp, z);
	ft_strdel(&temp);
	temp = ft_strjoin(info, ")");
	ft_strdel(&info);
	ft_strdel(&x);
	ft_strdel(&y);
	ft_strdel(&z);
	return (temp);
}

void	where_am_i(t_sdl *sdl)
{
	char *axis;
	char *aa;

	put_info(sdl, R_F, "Camera:", (cl_int3){10, 540, 30});
	axis = get_char_util("Rotation : (", sdl->rt.camera.rotation);
	put_info(sdl, R_F, axis, (cl_int3){10, 580, 10});
	ft_strdel(&axis);
	axis = get_char_util("Position : (", sdl->rt.camera.pos);
	put_info(sdl, R_F, axis, (cl_int3){10, 600, 10});
	ft_strdel(&axis);
	aa = ft_itoa(sdl->rt.camera.anti_aliasing);
	axis = ft_strjoin("Anti-aliasing: x", aa);
	put_info(sdl, R_F, axis, (cl_int3){10, 630, 14});
	ft_strdel(&axis);
	ft_strdel(&aa);
	aa = ft_itoa(sdl->rt.count_objects);
	axis = ft_strjoin("Objects: ", aa);
	put_info(sdl, R_F, axis, (cl_int3){10, 660, 14});
	ft_strdel(&axis);
	ft_strdel(&aa);
	aa = ft_itoa(sdl->rt.count_lights);
	axis = ft_strjoin("Lights: ", aa);
	put_info(sdl, R_F, axis, (cl_int3){10, 690, 14});
	ft_strdel(&axis);
	ft_strdel(&aa);
}

void	put_controls(t_sdl *sdl)
{
	put_info(sdl, G_F, "RTv1", (cl_int3){10, 10, 50});
	put_info(sdl, R_F, "Controls: ", (cl_int3){10, 120, 30});
	put_info(sdl, R_F, "W = UP", (cl_int3){10, 170, 15});
	put_info(sdl, R_F, "Q = DOWN", (cl_int3){10, 200, 15});
	put_info(sdl, R_F, "A = LEFT", (cl_int3){10, 230, 15});
	put_info(sdl, R_F, "S = RIGHT", (cl_int3){10, 260, 15});
	put_info(sdl, R_F, "Z = ROLL LEFT", (cl_int3){10, 290, 15});
	put_info(sdl, R_F, "X = ROLL RIGHT", (cl_int3){10, 320, 15});
	put_info(sdl, R_F, "+ = +Z_AXIS", (cl_int3){10, 350, 15});
	put_info(sdl, R_F, "- = -Z_AXIS", (cl_int3){10, 380, 15});
	put_info(sdl, R_F, "^ = -Y_AXIS", (cl_int3){10, 410, 15});
	put_info(sdl, R_F, "v = +Y_AXIS", (cl_int3){10, 440, 15});
	put_info(sdl, R_F, "> = +X_AXIS", (cl_int3){10, 470, 15});
	put_info(sdl, R_F, "< = -X_AXIS", (cl_int3){10, 500, 15});
	put_info(sdl, R_F, "----------------------", (cl_int3){0, 520, 15});
}

char	*get_num(char *info, int num)
{
	char *n;

	n = ft_itoa(num);
	info = ft_strjoin(info, n);
	ft_strdel(&n);
	return (info);
}
