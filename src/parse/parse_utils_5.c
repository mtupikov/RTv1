/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <mtupikov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 13:06:00 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/30 13:06:00 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt_v_1.h"

int		parse_light_type(char *line)
{
	if (!ft_strcmp(line, "ambient"))
		return (LGT_AMBIENT);
	else if (!ft_strcmp(line, "point"))
		return (LGT_POINT);
	else if (!ft_strcmp(line, "directional"))
		return (LGT_DIRECTIONAL);
	else
		error("Not valid light type.\n");
	return (0);
}

void	parse_light(t_sdl *sdl, int fd)
{
	char	*line;
	t_light	light;

	light = default_light();
	while (get_next_line(fd, &line) && !is_closing_brace(line))
	{
		if (ft_strstr(line, "type"))
			light.type = parse_light_type(check_equals(line) + 2);
		else if (ft_strstr(line, "intensity"))
			light.intensity = parse_float(check_equals(line) + 1, 1);
		else if (ft_strstr(line, "direction") || ft_strstr(line, "position"))
			light.start_point = parse_start_point(check_scope(line) + 1);
		else if (ft_strstr(line, "color"))
			light.color = parse_color(check_scope(line) + 1);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	sdl->lights[sdl->rt.count_lights] = light;
	sdl->rt.count_lights++;
}
