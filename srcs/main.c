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

void	ft_print_list(t_list *list)
{
	while (list)
	{
		while (list->p)
		{
			printf("{%f, %f, %f} R=%d G=%d B=%d\n", list->p->x, list->p->y, list->p->z, list->p->r, list->p->g, list->p->b);
			list->p = list->p->next;
		}
		list = list->next;
	}
}

int	draw(t_vars *v)
{
	
}

void	init_param(t_vars *v)
{
	v->x_angle = 0.95;
	v->y_angle = 0;
	v->z_angle = 0.785398;
	v->zoom = 1;
	v->length = 100;
}

int	input_manager(int keycode, t_vars *v)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(v->mlx, v->win);
		exit(0);
	}
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
		mlx_put_image_to_window(v.mlx, v.win, v.d.img, 0, 0);
		mlx_hook(v.win, 2, 1L<<0, input_manager, &v);
		/*printf("x_angle = %f\ny_angle = %f\nz_angle = %f\n", v.x_angle, v.y_angle, v.z_angle);
		printf("x_max = %d\ny_max = %d\nz_max = %d\n\n", v.x_max, v.y_max, v.z_max);*/
		//ft_print_list(v.p);
		mlx_loop(v.mlx);
		return (0);
	}
	return (write(2, "Error\n", 6), 1);
}
