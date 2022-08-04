/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:27:34 by mbenicho          #+#    #+#             */
/*   Updated: 2022/07/12 19:27:37 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_lstfree(t_point *lst)
{
	t_point	*tmp;

	while (lst)
	{
		tmp = lst->next;
		lst->x = 0;
		lst->y = 0;
		lst->z = 0;
		lst->r = 0;
		lst->g = 0;
		lst->b = 0;
		free(lst);
		lst = tmp;
	}
}

void	ft_lstadd_back(t_point **lst, t_point *new)
{
	t_point	*list;

	if (*lst)
	{
		list = *lst;
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else if (lst)
		*lst = new;
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
