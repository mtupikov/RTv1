/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_info_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <mtupikov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 23:40:00 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/29 23:40:00 by mtupikov         ###   ########.fr       */
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

char	*get_num(char *info, int num)
{
	char *n;

	n = ft_itoa(num);
	info = ft_strjoin(info, n);
	ft_strdel(&n);
	return (info);
}
