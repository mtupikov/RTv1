/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <mtupikov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 22:29:00 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/20 22:29:00 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt_v_1.h"

int		init_window(t_sdl *sdl)
{
	sdl->window = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH + SCREEN_OFFSET * 2,
	SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!sdl->window)
	{
		ft_printf("Window could not be created: %s\n", SDL_GetError());
		return (0);
	}
	if (TTF_Init() < 0)
		error((char *)SDL_GetError());
	sdl->screen = SDL_GetWindowSurface(sdl->window);
	return (1);
}

int		init_sdl(t_sdl *sdl)
{
	int success;

	success = 1;
	sdl->window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ft_printf("SDL init error: %s\n", SDL_GetError());
		success = 0;
	}
	else if (!init_window(sdl))
		success = 0;
	return (success);
}
