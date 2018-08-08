/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <mtupikov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 13:04:00 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/30 13:04:00 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt_v_1.h"

void	object_if(t_object_3d *object, char *line)
{
	if (ft_strstr(line, "center"))
		object->start_point = parse_start_point(check_scope(line) + 1);
	else if (ft_strstr(line, "radius"))
		object->radius = parse_float(check_equals(line) + 1, 0);
	else if (ft_strstr(line, "height"))
		object->height = parse_int(check_equals(line) + 1);
	else if (ft_strstr(line, "color"))
		object->color = parse_color(check_scope(line) + 1);
	else if (ft_strstr(line, "specular"))
		object->specular = parse_int(check_equals(line) + 1);
	else if (ft_strstr(line, "reflective"))
		object->reflective = parse_float(check_equals(line) + 1, 1);
	else if (ft_strstr(line, "normal"))
		object->normal = parse_start_point(check_scope(line) + 1);
	else if (ft_strstr(line, "angle"))
		object->angle = parse_float(check_equals(line) + 1, 0);
	else if (ft_strstr(line, "rot"))
		object->rot = parse_rotation(check_scope(line) + 1);
}

void	parse_plane(t_sdl *sdl, int fd)
{
	char		*line;
	t_object_3d	object;

	object = default_object();
	while (get_next_line(fd, &line) && !is_closing_brace(line))
	{
		object_if(&object, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	object.type = OBJ_PLANE;
	sdl->objects[sdl->rt.count_objects] = object;
	sdl->rt.count_objects++;
}

void	parse_sphere(t_sdl *sdl, int fd)
{
	char		*line;
	t_object_3d	object;

	object = default_object();
	while (get_next_line(fd, &line) && !is_closing_brace(line))
	{
		object_if(&object, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	object.type = OBJ_SPHERE;
	sdl->objects[sdl->rt.count_objects] = object;
	sdl->rt.count_objects++;
}

void	parse_cylinder(t_sdl *sdl, int fd)
{
	char		*line;
	t_object_3d	object;

	object = default_object();
	while (get_next_line(fd, &line) && !is_closing_brace(line))
	{
		object_if(&object, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	object.type = OBJ_CYLINDER;
	sdl->objects[sdl->rt.count_objects] = object;
	sdl->rt.count_objects++;
}

void	parse_cone(t_sdl *sdl, int fd)
{
	char		*line;
	t_object_3d	object;

	object = default_object();
	while (get_next_line(fd, &line) && !is_closing_brace(line))
	{
		object_if(&object, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	object.type = OBJ_CONE;
	sdl->objects[sdl->rt.count_objects] = object;
	sdl->rt.count_objects++;
}
