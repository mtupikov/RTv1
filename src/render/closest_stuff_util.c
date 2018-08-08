/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_stuff_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <mtupikov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 12:49:00 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/30 12:49:00 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt_v_1.h"

void	intersect_cone_util(t_object_3d cone, cl_float3 oc,
							cl_float3 point, t_roots *ks)
{
	cl_float2	m;

	m = (cl_float2){f_dot(point, cone.normal) *
	ks->t1 + f_dot(oc, cone.normal),
	f_dot(point, cone.normal) * ks->t2 + f_dot(oc, cone.normal)};
	if (cone.height > 0)
	{
		if (!(m.x > 0 && m.x < cone.height))
			ks->t1 = INF;
		if (!(m.y > 0 && m.y < cone.height))
			ks->t2 = INF;
	}
	if (cone.height < 0)
	{
		if (!(m.x < 0 && m.x > cone.height))
			ks->t1 = INF;
		if (!(m.y < 0 && m.y > cone.height))
			ks->t2 = INF;
	}
}

void	intersect_cylinder_util(t_object_3d cylinder, cl_float3 oc,
								cl_float3 point, t_roots *ks)
{
	cl_float2	m;

	m = (cl_float2){f_dot(point, cylinder.normal) * ks->t1 +
	f_dot(oc, cylinder.normal), f_dot(point, cylinder.normal) *
	ks->t2 + f_dot(oc, cylinder.normal)};
	if (!(m.x > 0 && m.x < cylinder.height))
		ks->t1 = INF;
	if (!(m.y > 0 && m.y < cylinder.height))
		ks->t2 = INF;
}

void	closest_inter_util(t_sdl *sdl, t_roots ks, cl_float3 mm,
		t_inter *inter)
{
	if (ks.t1 < inter->closest_t && ks.t1 >= mm.x && ks.t1 < mm.y)
	{
		inter->closest_t = ks.t1;
		inter->object = &sdl->objects[(int)mm.z];
	}
	if (ks.t2 < inter->closest_t && ks.t2 >= mm.x && ks.t2 < mm.y)
	{
		inter->closest_t = ks.t2;
		inter->object = &sdl->objects[(int)mm.z];
	}
}
