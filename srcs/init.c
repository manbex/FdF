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

static int	init_points(t_vars *v, t_point **list, int y, char **tab)
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
		new->next = NULL;
		ft_lstadd_back(list, new);
		i++;
	}
	return (0);
}

static int	check_size(int *x, char **tab)
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

static int	init_list(t_vars *v, char *line, int *x, int y)
{
	char	**tab;
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

static int	read_file(int fd, t_vars *v)
{
	char	*line;
	int		readed;
	int		x;
	int		y;

	readed = 1;
	x = 0;
	y = 0;
	while (readed)
	{
		readed = get_next_line(fd, &line);
		if (readed == -1 || (readed && !line))
			return (ft_free(line), ft_lstfree(v->p), 1);
		else if (readed)
			if (init_list(v, line, &x, y))
				return (1);
		y++;
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
	if (read_file(fd, v))
		return (1);
	return (0);
}
