/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <mtupikov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 17:57:00 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/28 17:57:00 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt_v_1.h"

void	put_text_to_font(t_sdl *sdl, TTF_Font *font, char *line)
{
	sdl->text = TTF_RenderText_Solid(font, line, (SDL_Color){0, 0, 0, 255});
}

void	put_info(t_sdl *sdl, char *font, char *text, cl_int3 k)
{
	if (!(sdl->font = TTF_OpenFont(font, k.z)))
		error((char *)TTF_GetError());
	put_text_to_font(sdl, sdl->font, text);
	SDL_BlitSurface(sdl->text, NULL, sdl->screen,
					&(SDL_Rect){k.x, k.y, 20, 20});
	TTF_CloseFont(sdl->font);
	SDL_FreeSurface(sdl->text);
}

cl_mem	create_cl_buffer(t_sdl *sdl, size_t size, cl_mem_flags flag, void *o)
{
	return (clCreateBuffer(sdl->cl.context, flag,
	size, o, &sdl->cl.ret));
}
