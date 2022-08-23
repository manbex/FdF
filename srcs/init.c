/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:56:10 by mbenicho          #+#    #+#             */
/*   Updated: 2022/07/12 18:56:15 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color(t_point *new, char *str)
{
	int	i;
	int size;
	char color[6];

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

int	init_points(t_vars *v, t_point **list, int y, char **tab)
{
	t_point	*new;
	int		i;

	i = 0;
	while (tab[i])
	{
		new = malloc(sizeof(*new));
		if (!new)
			return (1);
		new->x = i;
		new->y = y;
		if (parse_line(new, tab[i]))
			return (free(new), 1);
		if (new->x > v->x_max)
			v->x_max = new->x;
		if (new->y > v->y_max)
			v->y_max = new->y;
		if (new->z - new->x - new->y > v->z_max)
			v->z_max = new->z - new->x - new->y;
		new->next = NULL;
		ft_lstadd_back(list, new);
		i++;
	}
	return (0);
}

int	check_size(int *x, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	if (!(*x))
		*x = i;
	else if (i != *x)
		return (1);
	return (0);
}

int	init_list(t_vars *v, char *line, int *x, int y)
{
	char 	**tab;
	t_list	*new;

	tab = ft_split(line, ' ');
	free(line);
	if (!tab)
		return (1);
	new = malloc(sizeof(*new));
	if (!new)
		return (ft_free_tab(tab), ft_lstfree(v->p), 1);
	new->p = NULL;
	if (check_size(x, tab) || init_points(v, &(new->p), y, tab))
		return (ft_free_tab(tab), ft_lstfree(v->p), free(new), 1);
	ft_free_tab(tab);
	new->next = NULL;
	ft_lstadd_back1(&(v->p), new);
	return (0);
}

int	read_file(int fd, t_vars *v)
{
	char	*line;
	int 	readed;
	int		xy[2] = {0};

	readed = 1;
	while (readed)
	{
		readed = get_next_line(fd, &line);
		if (readed == -1 || (readed && !line))
			return (ft_free(line), ft_lstfree(v->p), 1);
		else if (readed)
			if (init_list(v, line, &xy[0], xy[1]))
				return (1);
		xy[1]++;
	}
	return (0);
}

int	init(char *file, t_vars *v)
{
	int		fd;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	v->p = NULL;
	v->x_max = 0;
	v->y_max = 0;
	v->z_max = -2147483648;
	if (read_file(fd, v))
		return (1);
	return (0);
}
