/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:55:51 by mbenicho          #+#    #+#             */
/*   Updated: 2022/07/12 18:55:54 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calc_point(t_vars *v, t_point *p)
{
	p->show = 1;
	p->px = p->x - ((double)v->x_max / 2);
	p->py = p->y - ((double)v->y_max / 2);
	p->pz = p->z * v->z_size;
	rotation_z(p, v->z_angle);
	rotation_x(p, v->x_angle);
	rotation_y(p, v->y_angle);
	p->i = (p->px * v->length) + v->x_off;
	p->j = (p->py * v->length) + v->y_off;
}

void	draw(t_vars *v)
{
	t_list	*lst;
	t_point	*tmp;
	t_point *tmp2;
	
	lst = v->p;
	
	while (lst)
	{
		tmp = lst->p;
		if (lst->next)
			tmp2 = lst->next->p;
		else
			tmp2 = NULL;
		while (tmp)
		{
			if (tmp == v->p->p)
				calc_point(v, tmp);
			if (tmp->next)
			{
				calc_point(v, tmp->next);
				if (!(tmp->i < 0 && tmp->next->i < 0)
					&& !(tmp->j < 0 && tmp->next->j < 0)
					&& !(tmp->i > WIN_X && tmp->next->i > WIN_X)
					&& !(tmp->j > WIN_Y && tmp->next->j > WIN_Y))
					plot_line(&v->d, tmp, tmp->next);
			}
			if (tmp2)
			{
				calc_point(v, tmp2);
				if (!(tmp->i < 0 && tmp2->i < 0)
					&& !(tmp->j < 0 && tmp2->j < 0)
					&& !(tmp->i > WIN_X && tmp2->i > WIN_X)
					&& !(tmp->j > WIN_Y && tmp2->j > WIN_Y))
					plot_line(&v->d, tmp, tmp2);
				tmp2 = tmp2->next;
			}
			tmp = tmp->next;
		}
		lst = lst->next;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->d.img, 0, 0);
	mlx_string_put(v->mlx, v->win, 20, 30, 0xFFFFFF, "Coucou c'est FdF !");
}

void	init_param(t_vars *v)
{
	v->x_angle = 0.95;
	v->y_angle = 0;
	v->z_angle = 0.785398;
	v->length = 1870 / ((v->x_max + v->y_max) * cos(0.785398));
	v->x_off = WIN_X / 2;
	v->y_off = WIN_Y / 2;
	v->z_size = 0.2;
	v->exit_code = 0;
}

int	exit_program(t_vars *v)
{
	if (v->d.img)
		mlx_destroy_image(v->mlx, v->d.img);
	if (v->win)
		mlx_destroy_window(v->mlx, v->win);
	mlx_loop_end(v->mlx);
	mlx_destroy_display(v->mlx);
	free(v->mlx);
	ft_lstfree(v->p);
	exit(v->exit_code);
}

int	input_manager(int keycode, t_vars *v)
{
	if (keycode == 65307)
		exit_program(v);
	else if ((keycode == 115 || keycode == 65364) && v->y_off > INT_MIN + TRANS)
		v->y_off -= TRANS;
	else if ((keycode == 119 || keycode == 65362) && v->y_off < INT_MAX - TRANS)
		v->y_off += TRANS;
	else if ((keycode == 100 || keycode == 65363) && v->x_off > INT_MIN + TRANS)
		v->x_off -= TRANS;
	else if ((keycode == 97 || keycode == 65361) && v->x_off < INT_MAX - TRANS)
		v->x_off += TRANS;
	else if (keycode == 114)
		v->x_angle -= ANGLE;
	else if (keycode == 1166)
		v->x_angle += ANGLE;
	else if (keycode == 102)
		v->y_angle -= ANGLE;
	else if (keycode == 103)
		v->y_angle += ANGLE;
	else if (keycode == 118)
		v->z_angle -= ANGLE;
	else if (keycode == 98)
		v->z_angle += ANGLE;
	else if (keycode == 117 && v->z_size > -5)
		v->z_size -= 0.1;
	else if (keycode == 105 && v->z_size < 5)
		v->z_size += 0.1;
	else if ((keycode == 122 || keycode == 65453) && v->length > 1)
	{
		v->length /= ZOOM;
		v->x_off = (WIN_X / 2) - (((WIN_X / 2) - v->x_off) / ZOOM);
		v->y_off = (WIN_Y / 2) - (((WIN_Y / 2) - v->y_off) / ZOOM);
	}
	else if (((keycode == 120 || keycode == 65451) && v->length < 10000)
			&& v->x_off < ((INT_MAX - (WIN_X / 2)) / ZOOM) + (WIN_X / 2)
				&& v->x_off < ((INT_MAX + ((WIN_X / 2)
				* (1 - ZOOM))) / ZOOM) - (WIN_X / 2) && v->y_off
				< ((INT_MAX - (WIN_Y / 2)) / ZOOM) + (WIN_Y / 2)
				&& v->y_off < ((INT_MAX + ((WIN_Y / 2)
				* (1 - ZOOM))) / ZOOM) - (WIN_Y / 2))
	{
		v->length *= ZOOM;
		v->x_off = (WIN_X / 2) - (((WIN_X / 2) - v->x_off) * ZOOM);
		v->y_off = (WIN_Y / 2) - (((WIN_Y / 2) - v->y_off) * ZOOM);
	}
	else if (keycode == 65289)
		init_param(v);
	mlx_destroy_image(v->mlx, v->d.img);
	v->d.img = mlx_new_image(v->mlx, WIN_X, WIN_Y);
	if (!v->d.img)
		return (write(2, "Error\n", 6), v->exit_code = 1, exit_program(v));
	v->d.addr = mlx_get_data_addr(v->d.img, &v->d.bpp,
			&v->d.length, &v->d.endian);
	draw(v);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	v;

	if (argc == 2 && ft_strlen(argv[1]) > 4
		&& argv[1][ft_strlen(argv[1]) - 1] == 'f'
		&& argv[1][ft_strlen(argv[1]) - 2] == 'd'
		&& argv[1][ft_strlen(argv[1]) - 3] == 'f'
		&& argv[1][ft_strlen(argv[1]) - 4] == '.')
	{
		if (init(argv[1], &v))
			return (write(2, "Error\n", 6), 1);
		init_param(&v);
		v.mlx = mlx_init();
		if (!v.mlx)
			return (ft_lstfree(v.p), write(2, "Error\n", 6), 1);
		v.win = NULL;
		v.d.img = mlx_new_image(v.mlx, WIN_X, WIN_Y);
		if (!v.d.img)
			return (write(2, "Error\n", 6), v.exit_code = 1, exit_program(&v));
		v.win = mlx_new_window(v.mlx, WIN_X, WIN_Y, "fdf");
		if (!v.win)
			return (write(2, "Error\n", 6), v.exit_code = 1, exit_program(&v));
		v.d.addr = mlx_get_data_addr(v.d.img, &v.d.bpp,
				&v.d.length, &v.d.endian);
		draw(&v);
		mlx_hook(v.win, 2, 1L << 0, input_manager, &v);
		mlx_hook(v.win, 33, 0, exit_program, &v);
		mlx_loop(v.mlx);
		return (0);
	}
	return (write(2, "Error\n", 6), 1);
}
