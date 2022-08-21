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
	p->px = p->x;
	p->py = p->y;
	p->pz = p->z / 5;
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
				plot_line(&(v->d), tmp->i, tmp->j, tmp->next->i, tmp->next->j);
			}
			if (tmp2)
			{
				calc_point(v, tmp2);
				plot_line(&(v->d), tmp->i, tmp->j, tmp2->i, tmp2->j);
				tmp2 = tmp2->next;
			}
			tmp = tmp->next;
		}
		lst = lst->next;
	}
}

void	init_param(t_vars *v)
{
	v->x_angle = 0.95;
	v->y_angle = 0;
	v->z_angle = 0.785398;
	v->zoom = 1;
	v->length = 3;
	v->x_off = 1000;
	v->y_off = 200;
}

int	input_manager(int keycode, t_vars *v)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(v->mlx, v->d.img);
		mlx_destroy_window(v->mlx, v->win);
		mlx_loop_end(v->mlx);
		mlx_destroy_display(v->mlx);
		free(v->mlx);
		ft_lstfree(v->p);
		exit(0);
	}
	if (keycode == 119)
		v->y_off -= 10;
	if (keycode == 115)
		v->y_off += 10;
	if (keycode == 97)
		v->x_off -= 10;
	if (keycode == 100)
		v->x_off += 10;
	if (keycode == 114)
		v->x_angle -= 0.1;
	if (keycode == 116)
		v->x_angle += 0.1;
	if (keycode == 102)
		v->y_angle -= 0.1;
	if (keycode == 103)
		v->y_angle += 0.1;
	if (keycode == 118)
		v->z_angle -= 0.1;
	if (keycode == 98)
		v->z_angle += 0.1;
	if (keycode == 105)
		init_param(v);
	printf("%d\n", keycode);
	mlx_destroy_image(v->mlx, v->d.img);
	v->d.img = mlx_new_image(v->mlx, 1920, 1080);
	v->d.addr = mlx_get_data_addr(v->d.img, &v->d.bpp, &v->d.length, &v->d.endian);
	mlx_put_image_to_window(v->mlx, v->win, v->d.img, 0, 0);
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
		v.win = mlx_new_window(v.mlx, 1920, 1080, "fdf");
		v.d.img = mlx_new_image(v.mlx, 1920, 1080);
		v.d.addr = mlx_get_data_addr(v.d.img, &v.d.bpp, &v.d.length, &v.d.endian);
		draw(&v);
		mlx_put_image_to_window(v.mlx, v.win, v.d.img, 0, 0);
		mlx_hook(v.win, 2, 1L<<0, input_manager, &v);
		mlx_loop(v.mlx);
		return (0);
	}
	return (write(2, "Error\n", 6), 1);
}
