/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <mtupikov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 06:50:00 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/16 06:50:00 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt_v_1.h"

void	parse_camera(t_sdl *sdl, int fd)
{
	char *line;

	while (get_next_line(fd, &line) && !is_closing_brace(line))
	{
		if (ft_strstr(line, "center"))
			sdl->rt.camera.pos = parse_start_point(check_scope(line) + 1);
		else if (ft_strstr(line, "rot"))
			sdl->rt.camera.rotation = parse_rotation(check_scope(line) + 1);
		else if (ft_strstr(line, "aa"))
			sdl->rt.camera.anti_aliasing = parse_int(check_equals(line) + 1);
		if (sdl->rt.camera.anti_aliasing < 1)
		{
			ft_strdel(&line);
			error("Parse error.\n");
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void	parse_file_util(t_sdl *sdl, int fd, char *line)
{
	if (!ft_strcmp(line, ""))
	{
		ft_strdel(&line);
		return ;
	}
	else if (!ft_strcmp(line, "plane {"))
		parse_plane(sdl, fd);
	else if (!ft_strcmp(line, "sphere {"))
		parse_sphere(sdl, fd);
	else if (!ft_strcmp(line, "cylinder {"))
		parse_cylinder(sdl, fd);
	else if (!ft_strcmp(line, "cone {"))
		parse_cone(sdl, fd);
	else if (!ft_strcmp(line, "light {"))
		parse_light(sdl, fd);
	else if (!ft_strcmp(line, "camera {"))
		parse_camera(sdl, fd);
	else
		error("Parse error.\n");
	ft_strdel(&line);
}

void	parse_file(t_sdl *sdl, int fd)
{
	char	*line;
	int		err;

	while ((err = get_next_line(fd, &line)) > 0)
		parse_file_util(sdl, fd, line);
	if (err < 0)
		error("Parse error.\n");
}

int		scene_parser(t_sdl *sdl, char *file)
{
	int		fd;

	if ((fd = open(file, O_RDONLY)) < 3)
		error("Parse error.\n");
	sdl->rt.count_lights = 0;
	sdl->rt.count_objects = 0;
	sdl->rt.camera = default_camera();
	parse_file(sdl, fd);
	close(fd);
	return (1);
}
