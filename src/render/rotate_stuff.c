/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <mtupikov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 17:50:00 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/28 17:50:00 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt_v_1.h"

cl_float3	rotate_x(cl_float3 t, cl_float3 rotation)
{
	cl_float3	v;

	v.x = t.x;
	v.y = (float)(t.y * cos(rotation.x * M_PI / 180) + t.z *
								sin(rotation.x * M_PI / 180));
	v.z = (float)(t.z * cos(rotation.x * M_PI / 180) - t.y *
								sin(rotation.x * M_PI / 180));
	return (v);
}

cl_float3	rotate_y(cl_float3 t, cl_float3 rotation)
{
	cl_float3	v;

	v.x = (float)(t.x * cos(rotation.y * M_PI / 180) - t.z *
								sin(rotation.y * M_PI / 180));
	v.y = t.y;
	v.z = (float)(t.z * cos(rotation.y * M_PI / 180) + t.x *
								sin(rotation.y * M_PI / 180));
	return (v);
}

cl_float3	rotate_z(cl_float3 t, cl_float3 rotation)
{
	cl_float3	v;

	v.x = (float)(t.x * cos(rotation.z * M_PI / 180) + t.y *
								sin(rotation.z * M_PI / 180));
	v.y = (float)(t.y * cos(rotation.z * M_PI / 180) - t.x *
								sin(rotation.z * M_PI / 180));
	v.z = t.z;
	return (v);
}

cl_float3	rotate(cl_float3 t, cl_float3 rotation)
{
	t = rotate_x(t, rotation);
	t = rotate_y(t, rotation);
	t = rotate_z(t, rotation);
	return (t);
}
