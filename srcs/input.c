/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:02:32 by mbenicho          #+#    #+#             */
/*   Updated: 2022/09/07 12:02:34 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

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

int	input_manager3(t_vars *v)
{
	mlx_destroy_image(v->mlx, v->d.img);
	v->d.img = mlx_new_image(v->mlx, WIN_X, WIN_Y);
	if (!v->d.img)
		return (write(2, "Error\n", 6), v->exit_code = 1, exit_program(v));
	v->d.addr = mlx_get_data_addr(v->d.img, &v->d.bpp,
			&v->d.length, &v->d.endian);
	draw(v);
	return (0);
}

int	input_manager2(int keycode, t_vars *v)
{
	if (keycode == 117 && v->z_size > -1)
		v->z_size -= 0.1;
	else if (keycode == 105 && v->z_size < 1)
		v->z_size += 0.1;
	else if ((keycode == 122 || keycode == 65453) && v->length > 1)
	{
		v->length /= ZOOM;
		v->x_off = (WIN_X / 2) - (((WIN_X / 2) - v->x_off) / ZOOM);
		v->y_off = (WIN_Y / 2) - (((WIN_Y / 2) - v->y_off) / ZOOM);
	}
	else if ((keycode == 120 || keycode == 65451) && v->length < 2000)
	{
		v->length *= ZOOM;
		v->x_off = (WIN_X / 2) - (((WIN_X / 2) - v->x_off) * ZOOM);
		v->y_off = (WIN_Y / 2) - (((WIN_Y / 2) - v->y_off) * ZOOM);
	}
	else if (keycode == 49)
		init_param(v);
	else if (keycode == 50)
		dimetric(v);
	else if (keycode == 51)
		trimetric(v);
	input_manager3(v);
	return (0);
}

int	input_manager(int keycode, t_vars *v)
{
	if (keycode == 65307)
		exit_program(v);
	else if (keycode == 115 || keycode == 65364)
		v->y_off -= TRANS;
	else if (keycode == 119 || keycode == 65362)
		v->y_off += TRANS;
	else if (keycode == 100 || keycode == 65363)
		v->x_off -= TRANS;
	else if (keycode == 97 || keycode == 65361)
		v->x_off += TRANS;
	else if (keycode == 114)
		v->x_angle -= ANGLE;
	else if (keycode == 116)
		v->x_angle += ANGLE;
	else if (keycode == 102)
		v->y_angle -= ANGLE;
	else if (keycode == 103)
		v->y_angle += ANGLE;
	else if (keycode == 118)
		v->z_angle -= ANGLE;
	else if (keycode == 98)
		v->z_angle += ANGLE;
	input_manager2(keycode, v);
	return (0);
}
