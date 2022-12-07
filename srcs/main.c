/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:55:51 by mbenicho          #+#    #+#             */
/*   Updated: 2022/09/07 11:54:46 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_param(t_vars *v)
{
	v->x_angle = 0.95;
	v->y_angle = 0;
	v->z_angle = 0.785398;
	v->length = (WIN_X - 50) / ((v->x_max + v->y_max) * cos(0.785398));
	v->x_off = WIN_X / 2;
	v->y_off = WIN_Y / 2;
	v->z_size = 0.2;
	v->exit_code = 0;
}

void	dimetric(t_vars *v)
{
	v->x_angle = 1.2;
	v->y_angle = 0;
	v->z_angle = 0.785398;
	v->length = (WIN_X - 50) / ((v->x_max + v->y_max) * cos(0.785398));
	v->x_off = WIN_X / 2;
	v->y_off = WIN_Y / 2;
	v->z_size = 0.2;
	v->exit_code = 0;
}

void	trimetric(t_vars *v)
{
	v->x_angle = 0.95;
	v->y_angle = 0;
	v->z_angle = 0.6;
	v->length = (WIN_X - 50) / ((v->x_max + v->y_max) * cos(0.785398));
	v->x_off = WIN_X / 2;
	v->y_off = WIN_Y / 2;
	v->z_size = 0.2;
	v->exit_code = 0;
}

int	fdf(t_vars *v)
{
	init_param(v);
	v->mlx = mlx_init();
	if (!v->mlx)
		return (ft_lstfree(v->p), write(2, "Error\n", 6), 1);
	v->d.img = mlx_new_image(v->mlx, WIN_X, WIN_Y);
	if (!v->d.img)
		return (write(2, "Error\n", 6), v->exit_code = 1, exit_program(v));
	v->win = mlx_new_window(v->mlx, WIN_X, WIN_Y, "fdf");
	if (!v->win)
		return (write(2, "Error\n", 6), v->exit_code = 1, exit_program(v));
	v->d.addr = mlx_get_data_addr(v->d.img, &v->d.bpp,
			&v->d.length, &v->d.endian);
	draw(v);
	mlx_hook(v->win, 2, 1L << 0, input_manager, v);
	mlx_hook(v->win, 33, 0, exit_program, v);
	mlx_loop(v->mlx);
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
		return (fdf(&v));
	}
	return (write(2, "Error\n", 6), 1);
}
