/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:23:25 by mbenicho          #+#    #+#             */
/*   Updated: 2022/07/12 15:23:28 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
	t_data	img;
	int	x;
	int	y;
}	t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	plot_line(t_data *data, int x0, int y0, int x1, int y1)
{
	int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
	int err = dx + dy, e2; /* error value e_xy */

	for (;;)
	{
		my_mlx_pixel_put(data, x0, y0, 0x00FF0000);
		if (x0 == x1 && y0 == y1) break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	}
}

int	test(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == 97)
		vars->x += 10;
	if (keycode == 100)
		vars->x -= 10;
	if (keycode == 119)
		vars->y += 10;
	if (keycode == 115)
		vars->y -= 10;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, vars->x, vars->y);
	return (0);
}

void	grid(t_data *img)
{
	for (int y = 100; y <= 400; y += 20)
		for (int x = 100; x <= 400; x++)
			my_mlx_pixel_put(img, x, y, 0x00FF0000);
	
	for (int y = 100; y <= 400; y += 20)
		for (int x = 100; x <= 400; x++)
			my_mlx_pixel_put(img, y, x, 0x00FF0000);
}

int	main()
{
	t_vars	vars;
	t_data	img;
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 700, "fdf");
	img.img = mlx_new_image(vars.mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	grid(&img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	vars.img = img;
	vars.x = 0;
	vars.y = 0;
	mlx_hook(vars.win, 2, 1L<<0, test, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
