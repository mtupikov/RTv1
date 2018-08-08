/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <mtupikov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 17:49:00 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/28 17:49:00 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt_v_1.h"

t_roots	intersect_cone(t_object_3d cone, cl_float3 o, cl_float3 point)
{
	t_roots		ks;
	float		d;
	cl_float3	kk;
	float		k;
	cl_float3	oc;

	ks.t1 = INF;
	ks.t2 = INF;
	oc = subtract_3d_vector(o, cone.start_point);
	cone.normal = rotate(cone.normal, cone.rot);
	k = 1 + cone.angle * cone.angle;
	kk.x = f_dot(point, point) - k * powf(f_dot(point, cone.normal), 2.0f);
	kk.y = (f_dot(point, oc) - k * f_dot(point, cone.normal) *
	f_dot(oc, cone.normal)) * 2.0f;
	kk.z = f_dot(oc, oc) - k * powf(f_dot(oc, cone.normal), 2.0f);
	d = kk.y * kk.y - 4 * kk.x * kk.z;
	if (d < 0)
		return (ks);
	ks.t1 = (-1 * kk.y - sqrtf(d)) / (2 * kk.x);
	ks.t2 = (-1 * kk.y + sqrtf(d)) / (2 * kk.x);
	if (cone.height == 0)
		return (ks);
	intersect_cone_util(cone, oc, point, &ks);
	return (ks);
}

t_roots	intersect_sphere(t_object_3d sphere, cl_float3 o, cl_float3 point)
{
	t_roots		ks;
	float		d;
	cl_float3	kk;
	cl_float3	oc;

	ks.t1 = INF;
	ks.t2 = INF;
	oc = subtract_3d_vector(o, sphere.start_point);
	kk.x = f_dot(point, point);
	kk.y = 2.0f * f_dot(oc, point);
	kk.z = f_dot(oc, oc) - powf((float)sphere.radius, 2.0f);
	d = kk.y * kk.y - 4 * kk.x * kk.z;
	if (d < 0)
		return (ks);
	ks.t1 = (-kk.y + sqrtf(d) / (2.0f * kk.x));
	ks.t2 = (-kk.y - sqrtf(d) / (2.0f * kk.x));
	return (ks);
}

t_roots	intersect_cylinder(t_object_3d cylinder, cl_float3 o, cl_float3 point)
{
	t_roots		ks;
	float		d;
	cl_float3	kk;
	cl_float3	oc;

	ks.t1 = INF;
	ks.t2 = INF;
	oc = subtract_3d_vector(o, cylinder.start_point);
	cylinder.normal = rotate(cylinder.normal, cylinder.rot);
	kk.x = f_dot(point, point) - powf(f_dot(point, cylinder.normal), (float)2);
	kk.y = (f_dot(point, oc) - f_dot(point, cylinder.normal) *
	f_dot(oc, cylinder.normal)) * 2;
	kk.z = f_dot(oc, oc) - powf(f_dot(oc, cylinder.normal), (float)2) -
	powf(cylinder.radius, (float)2);
	d = kk.y * kk.y - 4 * kk.x * kk.z;
	if (d < 0)
		return (ks);
	ks.t1 = (-1 * kk.y - sqrtf(d)) / (2 * kk.x);
	ks.t2 = (-1 * kk.y + sqrtf(d)) / (2 * kk.x);
	if (cylinder.height == 0)
		return (ks);
	intersect_cylinder_util(cylinder, oc, point, &ks);
	return (ks);
}

t_roots	intersect_plane(t_object_3d plane, cl_float3 o, cl_float3 point)
{
	t_roots		ks;
	float		d;
	cl_float3	oc;

	ks.t1 = INF;
	ks.t2 = INF;
	oc = subtract_3d_vector(o, plane.start_point);
	plane.normal = rotate(plane.normal, plane.rot);
	if (f_dot(plane.normal, point) != 0)
	{
		d = -f_dot(plane.normal, oc) / f_dot(plane.normal, point);
		if (d > 0.0001)
		{
			ks.t1 = d;
			ks.t2 = d;
		}
	}
	return (ks);
}

t_inter	closest_inter(t_sdl *sdl, cl_float3 o, cl_float3 point)
{
	t_inter	inter;
	t_roots	ks;
	int		i;

	inter.closest_t = INF;
	inter.object = NULL;
	ks.t1 = INF;
	ks.t2 = INF;
	i = -1;
	while (++i < sdl->rt.count_objects)
	{
		if (sdl->objects[i].type == OBJ_CYLINDER)
			ks = intersect_cylinder(sdl->objects[i], o, point);
		else if (sdl->objects[i].type == OBJ_PLANE)
			ks = intersect_plane(sdl->objects[i], o, point);
		else if (sdl->objects[i].type == OBJ_SPHERE)
			ks = intersect_sphere(sdl->objects[i], o, point);
		else if (sdl->objects[i].type == OBJ_CONE)
			ks = intersect_cone(sdl->objects[i], o, point);
		closest_inter_util(sdl, ks, (cl_float3){1, INF, i}, &inter);
	}
	return (inter);
}
