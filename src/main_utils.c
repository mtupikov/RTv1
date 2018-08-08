/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <mtupikov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 12:53:00 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/30 12:53:00 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt_v_1.h"

void	error(char *line)
{
	ft_printf(line);
	exit(2);
}

void	rotation_manager(t_sdl *sdl)
{
	if (sdl->event.key.keysym.sym == SDLK_q)
		sdl->rt.camera.rotation.x += 2;
	else if (sdl->event.key.keysym.sym == SDLK_w)
		sdl->rt.camera.rotation.x -= 2;
	else if (sdl->event.key.keysym.sym == SDLK_a)
		sdl->rt.camera.rotation.y += 2;
	else if (sdl->event.key.keysym.sym == SDLK_s)
		sdl->rt.camera.rotation.y -= 2;
	else if (sdl->event.key.keysym.sym == SDLK_z)
		sdl->rt.camera.rotation.z += 2;
	else if (sdl->event.key.keysym.sym == SDLK_x)
		sdl->rt.camera.rotation.z -= 2;
	if (sdl->rt.camera.rotation.x < 0)
		sdl->rt.camera.rotation.x = 360;
	if (sdl->rt.camera.rotation.x > 360)
		sdl->rt.camera.rotation.x = 0;
	if (sdl->rt.camera.rotation.y < 0)
		sdl->rt.camera.rotation.y = 360;
	if (sdl->rt.camera.rotation.y > 360)
		sdl->rt.camera.rotation.y = 0;
	if (sdl->rt.camera.rotation.z < 0)
		sdl->rt.camera.rotation.z = 360;
	if (sdl->rt.camera.rotation.z > 360)
		sdl->rt.camera.rotation.z = 0;
}

void	movement_manager(t_sdl *sdl)
{
	if (sdl->event.key.keysym.sym == SDLK_UP)
		sdl->rt.camera.pos.y -= 1;
	else if (sdl->event.key.keysym.sym == SDLK_DOWN)
		sdl->rt.camera.pos.y += 1;
	else if (sdl->event.key.keysym.sym == SDLK_LEFT)
		sdl->rt.camera.pos.x -= 1;
	else if (sdl->event.key.keysym.sym == SDLK_RIGHT)
		sdl->rt.camera.pos.x += 1;
	else if (sdl->event.key.keysym.sym == SDLK_EQUALS)
		sdl->rt.camera.pos.z += 1;
	else if (sdl->event.key.keysym.sym == SDLK_MINUS)
		sdl->rt.camera.pos.z -= 1;
}
