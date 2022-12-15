/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:02:46 by mbenicho          #+#    #+#             */
/*   Updated: 2022/09/07 15:54:16 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calc_point(t_vars *v, t_point *p)
{
	p->px = p->x - ((double)v->x_max / 2);
	p->py = p->y - ((double)v->y_max / 2);
	p->pz = p->z * v->z_size;
	rotation_z(p, v->z_angle);
	rotation_x(p, v->x_angle);
	rotation_y(p, v->y_angle);
	p->i = (p->px * v->length) + v->x_off;
	p->j = (p->py * v->length) + v->y_off;
}

void	draw2(t_vars *v, t_point **tmp, t_point **tmp2)
{
	if (*tmp == v->p->p)
		calc_point(v, *tmp);
	if ((*tmp)->next)
	{
		calc_point(v, (*tmp)->next);
		if (!((*tmp)->i < 0 && (*tmp)->next->i < 0)
			&& !((*tmp)->j < 0 && (*tmp)->next->j < 0)
			&& !((*tmp)->i > WIN_X && (*tmp)->next->i > WIN_X)
			&& !((*tmp)->j > WIN_Y && (*tmp)->next->j > WIN_Y))
			plot_line(&v->d, *tmp, (*tmp)->next);
	}
	if (*tmp2)
	{
		calc_point(v, *tmp2);
		if (!((*tmp)->i < 0 && (*tmp2)->i < 0)
			&& !((*tmp)->j < 0 && (*tmp2)->j < 0)
			&& !((*tmp)->i > WIN_X && (*tmp2)->i > WIN_X)
			&& !((*tmp)->j > WIN_Y && (*tmp2)->j > WIN_Y))
			plot_line(&v->d, *tmp, *tmp2);
		*tmp2 = (*tmp2)->next;
	}
	*tmp = (*tmp)->next;
}

void	show_instructions(t_vars *v)
{
	mlx_string_put(v->mlx, v->win, 10, 30, 0xFFFFFF, "Hide controls: H");
	mlx_string_put(v->mlx, v->win, 20, 45, 0xFFFFFF,
		"Translate: W, A, S, D or arrow keys");
	mlx_string_put(v->mlx, v->win, 20, 60, 0xFFFFFF, "Rotate x: R, T");
	mlx_string_put(v->mlx, v->win, 20, 75, 0xFFFFFF, "Rotate y: F, G");
	mlx_string_put(v->mlx, v->win, 20, 90, 0xFFFFFF, "Rotate z: C, V");
	mlx_string_put(v->mlx, v->win, 20, 105, 0xFFFFFF, "Zoom in: X or +");
	mlx_string_put(v->mlx, v->win, 20, 120, 0xFFFFFF, "Zoom out: Z or -");
	mlx_string_put(v->mlx, v->win, 20, 135, 0xFFFFFF, "Increase size: I");
	mlx_string_put(v->mlx, v->win, 20, 150, 0xFFFFFF, "Decrease size:: U");
	mlx_string_put(v->mlx, v->win, 20, 165, 0xFFFFFF,
		"Isometric projection: 1");
	mlx_string_put(v->mlx, v->win, 20, 180, 0xFFFFFF, "Dimetric projection: 2");
	mlx_string_put(v->mlx, v->win, 20, 195, 0xFFFFFF,
		"Trimetric projection: 3");
	mlx_string_put(v->mlx, v->win, 20, 210, 0xFFFFFF, "Quit: ESC");
}

void	draw(t_vars *v)
{
	t_list	*lst;
	t_point	*tmp;
	t_point	*tmp2;

	lst = v->p;
	while (lst)
	{
		tmp = lst->p;
		if (lst->next)
			tmp2 = lst->next->p;
		else
			tmp2 = NULL;
		while (tmp)
			draw2(v, &tmp, &tmp2);
		lst = lst->next;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->d.img, 0, 0);
	if (v->show == 1)
		show_instructions(v);
	else
		mlx_string_put(v->mlx, v->win, 10, 30, 0xFFFFFF, "Show controls: H");
}
