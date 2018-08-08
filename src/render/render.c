/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <mtupikov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 22:42:00 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/20 22:42:00 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include "../../inc/rt_v_1.h"

void	kernel_start(t_sdl *sdl)
{
	sdl->cl.obj = create_cl_buffer(sdl, sizeof(t_object_3d) *
			sdl->rt.count_objects, CL_MEM_USE_HOST_PTR, sdl->objects);
	sdl->cl.lgt = create_cl_buffer(sdl, sizeof(t_light) *
			sdl->rt.count_lights, CL_MEM_USE_HOST_PTR, sdl->lights);
	sdl->cl.col = create_cl_buffer(sdl, sizeof(int) * (SCREEN_WIDTH +
			SCREEN_OFFSET * 2) * SCREEN_HEIGHT, CL_MEM_READ_WRITE, NULL);
	clSetKernelArg(sdl->cl.kernel, 0, sizeof(t_rt), &sdl->rt);
	clSetKernelArg(sdl->cl.kernel, 1, sizeof(cl_mem), (void *)&sdl->cl.col);
	clSetKernelArg(sdl->cl.kernel, 2, sizeof(cl_mem), (void *)&sdl->cl.obj);
	clSetKernelArg(sdl->cl.kernel, 3, sizeof(cl_mem), (void *)&sdl->cl.lgt);
	clEnqueueNDRangeKernel(sdl->cl.command_queue, sdl->cl.kernel, 2, NULL,
	(size_t[3]){SCREEN_WIDTH, SCREEN_HEIGHT, 0}, NULL, 0, NULL, NULL);
	clEnqueueReadBuffer(sdl->cl.command_queue, sdl->cl.col, CL_TRUE, 0,
	sizeof(int) * (SCREEN_WIDTH + SCREEN_OFFSET * 2) * SCREEN_HEIGHT,
	(int *)sdl->screen->pixels, 0, NULL, NULL);
	clReleaseMemObject(sdl->cl.lgt);
	clReleaseMemObject(sdl->cl.obj);
	clReleaseMemObject(sdl->cl.col);
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

void	put_image(t_sdl *sdl)
{
	kernel_start(sdl);
	put_controls(sdl);
	where_am_i(sdl);
	if (sdl->in.object != NULL)
		type_object(sdl);
	else
		put_info(sdl, R_F, "No object selected.", (cl_int3){1285, 10, 15});
	SDL_UpdateWindowSurface(sdl->window);
}