/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <mtupikov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 17:46:00 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/28 17:46:00 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt_v_1.h"

float		f_dot(cl_float3 t1, cl_float3 t2)
{
	float ret;

	ret = t1.x * t2.x + t1.y * t2.y + t1.z * t2.z;
	return (ret);
}

cl_float3	subtract_3d_vector(cl_float3 t1, cl_float3 t2)
{
	cl_float3 ret;

	ret.x = t1.x - t2.x;
	ret.y = t1.y - t2.y;
	ret.z = t1.z - t2.z;
	return (ret);
}
