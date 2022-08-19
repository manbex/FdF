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

# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
#include <math.h>
# include <stdio.h>

typedef struct s_dat
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_dat;

typedef struct	s_var
{
	void	*mlx;
	void	*win;
	t_dat	img;
	int	x;
	int	y;
}	t_var;

static void	my_mlx_pixel_put(t_dat *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	plot_line(t_dat *data, int x0, int y0, int x1, int y1)
{
	int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
	int err = dx + dy, e2; /* error value e_xy */

	for (;;)
	{
		my_mlx_pixel_put(data, x0, y0, 0xFF00FF);
		if (x0 == x1 && y0 == y1) break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	}
}

int	test(int keycode, t_var *vars)
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

void	rotation_x(double *px, double *py, double *pz)
{
	//double	a = 0;
	double	a = 0.95;

	double	x = *px;
	double	y = *py;
	double	z = *pz;
	*px = x;
	*py = (y * cos(a)) - (z * sin(a));
	*pz = (y * sin(a)) + (z * cos(a));
}

void	rotation_y(double *px, double *py, double *pz)
{
	double	a = 0;

	double	x = *px;
	double	y = *py;
	double	z = *pz;
	*px = (x * cos(a)) + (z * sin(a));
	*py = y;
	*pz = (z * cos(a)) - (x * sin(a));
}

void	rotation_z(double *px, double *py, double *pz)
{
	//double	a = 0;
	double	a = 0.785398;

	double	x = *px;
	double	y = *py;
	double	z = *pz;
	*px = (x * cos(a)) - (y * sin(a));
	*py = (x * sin(a)) + (y * cos(a));
	*pz = z;
}

void	iso(int *px, int *py)
{
	double a = 0;

	int	x = *px;
	int	y = *py;

	*px = (x * cos(a)) - (y * sin(a));
	*py = (x * sin(a)) + (y * cos(a));
}

void	grid(t_dat *img)
{
	double	a[3] = {0, 0, 0};
	double	b[3] = {1, 0, 0};
	double	c[3] = {0, 1, 0};
	double	d[3] = {1, 1, 0};
	double	p[2][3] = {{100, 0, 0}, {0, 100, 0}};
	int	i = 300;

	rotation_x(&a[0], &a[1], &a[2]);
	rotation_x(&b[0], &b[1], &b[2]);
	rotation_x(&c[0], &c[1], &c[2]);
	rotation_x(&d[0], &d[1], &d[2]);

	rotation_z(&a[0], &a[1], &a[2]);
	rotation_z(&b[0], &b[1], &b[2]);
	rotation_z(&c[0], &c[1], &c[2]);
	rotation_z(&d[0], &d[1], &d[2]);

	
	
	rotation_y(&a[0], &a[1], &a[2]);
	rotation_y(&b[0], &b[1], &b[2]);
	rotation_y(&c[0], &c[1], &c[2]);
	rotation_y(&d[0], &d[1], &d[2]);

	int	p1[] = {(a[0] * p[0][0]) + (a[1] * p[0][1]) + (a[2] * p[0][2]), (a[0] * p[1][0]) + (a[1] * p[1][1]) + (a[2] * p[1][2])};
	int	p2[] = {(b[0] * p[0][0]) + (b[1] * p[0][1]) + (b[2] * p[0][2]), (b[0] * p[1][0]) + (b[1] * p[1][1]) + (b[2] * p[1][2])};
	int	p3[] = {(c[0] * p[0][0]) + (c[1] * p[0][1]) + (c[2] * p[0][2]), (c[0] * p[1][0]) + (c[1] * p[1][1]) + (c[2] * p[1][2])};
	int	p4[] = {(d[0] * p[0][0]) + (d[1] * p[0][1]) + (d[2] * p[0][2]), (d[0] * p[1][0]) + (d[1] * p[1][1]) + (d[2] * p[1][2])};

	//iso(&p1[0], &p1[1]);
	//iso(&p2[0], &p2[1]);
	//iso(&p3[0], &p3[1]);
	//iso(&p4[0], &p4[1]);
	p1[0] += i;
	p1[1] += i;
	p2[0] += i;
	p2[1] += i;
	p3[0] += i;
	p3[1] += i;
	p4[0] += i;
	p4[1] += i;
	printf("angle = %f rad\n", atan((double)(p2[1] - p1[1]) / (double)(p2[0] - p1[0])));
	plot_line(img, p1[0], p1[1], p2[0], p2[1]);
	plot_line(img, p2[0], p2[1], p4[0], p4[1]);
	plot_line(img, p3[0], p3[1], p4[0], p4[1]);
	plot_line(img, p3[0], p3[1], p1[0], p1[1]);
}

int	main()
{
	t_var	vars;
	t_dat	img;
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "fdf");
	img.img = mlx_new_image(vars.mlx, 20000, 20000);
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
