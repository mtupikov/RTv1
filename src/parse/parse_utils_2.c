/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <mtupikov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 22:22:00 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/20 22:22:00 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt_v_1.h"

char		*check_equals(char *line)
{
	char *ret;

	ret = ft_strchr(line, '=');
	if (!ret)
		error("Parse error.\n");
	return (ret);
}

char		*check_scope(char *line)
{
	char *ret;

	ret = ft_strchr(line, '(');
	if (!ret)
		error("Parse error.\n");
	return (ret);
}

int			parse_int(char *line)
{
	int r;

	if (!check_num(line))
		error("Bad int.\n");
	r = (int)ft_atoi(line);
	return (r);
}

float		parse_float(char *line, int lim)
{
	double	ref;
	int		i;

	if (!check_double(line))
		error("Bad float.\n");
	i = -1;
	while (line[++i])
	{
		if (line[i] != ' ')
			break ;
	}
	ref = ft_atof(line + 1);
	if (lim && (ref < 0 || ref > 1.0))
		error("Must be 0 <= x <= 1.\n");
	return ((float)ref);
}

cl_int3		parse_color(char *line)
{
	char	**split;
	cl_int3	color;
	int		i;

	line[ft_strlen(line) - 1] = '\0';
	split = ft_strsplit(line, ',');
	if (ft_strsplit_count(split) != 3)
		error("Bad coordinates.\n");
	i = -1;
	while (split[++i])
		if (!check_num(split[i]))
		{
			ft_splitdel(&split);
			error("Bad color.\n");
		}
	color.x = (Uint8)ft_atoi(split[0]);
	color.y = (Uint8)ft_atoi(split[1]);
	color.z = (Uint8)ft_atoi(split[2]);
	ft_splitdel(&split);
	return (color);
}
