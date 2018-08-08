/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <mtupikov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 22:20:00 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/20 22:20:00 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt_v_1.h"

int			is_closing_brace(char *str)
{
	return ((int)ft_strstr(str, "}"));
}

int			check_double(char *c)
{
	int		i;

	i = -1;
	if (c[0] == ' ' && c[1] == '-')
		i += 2;
	else if (c[0] == '-')
		++i;
	else if (c[0] == ' ')
		++i;
	while (c[++i])
	{
		if (c[i] == '.')
			continue ;
		if (!ft_isdigit(c[i]))
			return (0);
	}
	return (1);
}

int			check_num(char *c)
{
	int		i;
	long	t;

	i = -1;
	if (c[0] == ' ' && c[1] == '-')
		i += 2;
	else if (c[0] == '-')
		++i;
	else if (c[0] == ' ')
		++i;
	while (c[++i])
		if (!ft_isdigit(c[i]))
			return (0);
	t = ft_atoi(c);
	if (t < INT32_MIN || t > INT32_MAX)
		return (0);
	return (1);
}

cl_float3	parse_start_point(char *line)
{
	char		**split;
	cl_float3	start;
	int			i;

	line[ft_strlen(line) - 1] = '\0';
	split = ft_strsplit(line, ',');
	if (ft_strsplit_count(split) != 3)
		error("Bad coordinates.\n");
	i = -1;
	while (split[++i])
		if (!check_double(split[i]))
		{
			ft_splitdel(&split);
			error("Bad coordinates.\n");
		}
	start.x = (float)ft_atof(split[0]);
	start.y = (float)ft_atof(split[1] + 1);
	start.z = (float)ft_atof(split[2] + 1);
	ft_splitdel(&split);
	return (start);
}
