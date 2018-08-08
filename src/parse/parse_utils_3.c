/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <mtupikov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 15:37:00 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/22 15:37:00 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt_v_1.h"

cl_float3	add_rotation(float a, float b, float g)
{
	cl_float3 rotation;

	rotation.x = a;
	rotation.y = b;
	rotation.z = g;
	return (rotation);
}

cl_float3	parse_rotation(char *line)
{
	char		**split;
	cl_float3	rot;
	int			i;

	line[ft_strlen(line) - 1] = '\0';
	split = ft_strsplit(line, ',');
	if (ft_strsplit_count(split) != 3)
		error("Bad coordinates.\n");
	i = -1;
	while (split[++i])
		if (!check_double(split[i]))
		{
			ft_printf("%s\n", split[i]);
			ft_splitdel(&split);
			error("Bad coordinates.\n");
		}
	rot.x = (float)ft_atof(split[0]);
	rot.y = (float)ft_atof(split[1] + 1);
	rot.z = (float)ft_atof(split[2] + 1);
	ft_splitdel(&split);
	return (rot);
}

t_object_3d	default_object(void)
{
	t_object_3d	object;

	object.color = (cl_int3){255, 0, 0};
	object.normal = (cl_float3){0, 0, 1};
	object.reflective = 0.3;
	object.specular = 10;
	object.start_point = (cl_float3){0, 0, 0};
	object.angle = 0.5;
	object.radius = 1;
	object.height = 0;
	object.rot = (cl_float3){0, 0, 0};
	return (object);
}

t_camera	default_camera(void)
{
	t_camera cam;

	cam.rotation = add_rotation(0, 0, 0);
	cam.pos = (cl_float3){0, 0, 0};
	cam.anti_aliasing = 1;
	return (cam);
}

t_light		default_light(void)
{
	t_light lgt;

	lgt.color = (cl_int3){255, 0, 0};
	lgt.start_point = (cl_float3){1, 1, 1};
	lgt.type = LGT_AMBIENT;
	lgt.intensity = 0.2;
	return (lgt);
}
