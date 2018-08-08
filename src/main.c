/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 13:14:29 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/30 13:14:31 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt_v_1.h"

void	setup_cl(t_sdl *sdl)
{
	int		fp;
	char	*source_str;
	size_t	source_size;

	fp = open("kernel.cl", O_RDONLY);
	if (!fp)
		error("Failed to load kernel.\n");
	source_str = (char *)malloc(MAX_SOURCE_SIZE);
	source_size = (size_t)read(fp, source_str, MAX_SOURCE_SIZE);
	close(fp);
	sdl->cl.ret = clGetPlatformIDs(1, &sdl->cl.platform_id,
	&sdl->cl.ret_num_platforms);
	sdl->cl.ret = clGetDeviceIDs(sdl->cl.platform_id, CL_DEVICE_TYPE_DEFAULT,
	1, &sdl->cl.device_id, &sdl->cl.ret_num_devices);
	sdl->cl.context = clCreateContext(NULL, 1, &sdl->cl.device_id, NULL,
	NULL, &sdl->cl.ret);
	sdl->cl.command_queue = clCreateCommandQueue(sdl->cl.context,
	sdl->cl.device_id, 0, &sdl->cl.ret);
	sdl->cl.program = clCreateProgramWithSource(sdl->cl.context, 1,
	(const char **)&source_str, (const size_t *)&source_size, &sdl->cl.ret);
	sdl->cl.ret = clBuildProgram(sdl->cl.program, 1, &sdl->cl.device_id, NULL,
	NULL, NULL);
	sdl->cl.kernel = clCreateKernel(sdl->cl.program, "render", &sdl->cl.ret);
	free(source_str);
}

void	select_object(t_sdl *sdl)
{
	int			x;
	int			y;
	cl_float3	p;

	SDL_GetMouseState(&x, &y);
	p = (cl_float3){(float)((x - SCREEN_OFFSET - SCREEN_WIDTH / 2)
	* 1.0 / SCREEN_WIDTH), (float)((y - SCREEN_HEIGHT / 2) * 1.0 /
	SCREEN_HEIGHT), 1.0f};
	p = rotate(p, sdl->rt.camera.rotation);
	sdl->in = closest_inter(sdl, sdl->rt.camera.pos, p);
}

void	main_loop(t_sdl *sdl)
{
	while (SDL_PollEvent(&sdl->event))
	{
		if (sdl->event.type == SDL_QUIT || (sdl->event.type == SDL_KEYDOWN &&
				sdl->event.key.keysym.sym == SDLK_ESCAPE))
			sdl->quit = 1;
		if (sdl->event.type == SDL_KEYDOWN)
		{
			rotation_manager(sdl);
			movement_manager(sdl);
		}
		if (sdl->event.type == SDL_MOUSEBUTTONDOWN)
			select_object(sdl);
	}
	put_image(sdl);
}

int		main(int argc, char **argv)
{
	t_sdl	sdl;

	sdl.objects = ft_memalloc(sizeof(t_object_3d) * 100);
	sdl.lights = ft_memalloc(sizeof(t_light) * 100);
	if (argc != 2)
		error("Usage: ./RTv1 [scene]\n");
	scene_parser(&sdl, argv[1]);
	if (!init_sdl(&sdl))
		exit(2);
	setup_cl(&sdl);
	sdl.quit = 0;
	while (!sdl.quit)
		main_loop(&sdl);
	return (0);
}
