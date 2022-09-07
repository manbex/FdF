/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:21:37 by mbenicho          #+#    #+#             */
/*   Updated: 2022/09/07 10:21:38 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_color(t_point *new, char *str)
{
	int		i;
	int		size;
	char	color[6];

	size = ft_strlen(str);
	if (size > 6)
		return (1);
	i = 6;
	while (i--)
	{
		size--;
		color[i] = '0';
		if (size >= 0)
		{
			color[i] = str[size];
			if (!((str[size] >= '0' && str[size] <= '9')
					|| (str[size] >= 'a' && str[size] <= 'f')
					|| (str[size] >= 'A' && str[size] <= 'F')))
				return (1);
		}
	}
	new->r = ft_atoi_hex(color[0], color[1]);
	new->g = ft_atoi_hex(color[2], color[3]);
	new->b = ft_atoi_hex(color[4], color[5]);
	return (0);
}

int	parse_line(t_point *new, char *str)
{
	int	i;

	new->z = ft_atoi(str);
	while ((*str >= '0' && *str <= '9') || *str == '-')
		str++;
	if (!*str)
	{
		new->r = 0xff;
		new->g = 0xff;
		new->b = 0xff;
		return (0);
	}
	if (str[0] == ',' && str[1] == '0' && (str[2] == 'x' || str[2] == 'X'))
	{
		str += 3;
		i = ft_strlen(str);
		if (i == 0 || get_color(new, str))
			return (1);
		return (0);
	}
	return (1);
}
