#include "fdf.h"

void	my_mlx_pixel_put(t_data *d, int x, int y, int color)
{
	char	*dst;

	dst = d->addr + (y * d->length + x * (d->bpp / 8));
	*(unsigned int *)dst = color;
}

static t_line	bresenham_init(t_point *p1, t_point *p2)
{
	t_line	l;

	l.x = p1->i;
	l.y = p1->j;
	l.dx = abs(p2->i - p1->i);
	l.dy = -abs(p2->j - p1->j);
	l.err = l.dx + l.dy;
	l.i = 0;
	l.size = 1;
	l.sx = 1;
	l.sy = 1;
	if (p1->i >= p2->i)
		l.sx = -1;
	if (p1->j >= p2->j)
		l.sy = -1;
	if (l.dx >= -l.dy)
		l.size = l.dx;
	else
		l.size = -l.dy;
	return (l);
}

static int	get_color(t_line l, t_point *p1, t_point *p2)
{
	int	r;
	int	g;
	int	b;
	if (l.size != 0)
	{
		r = p1->r + ((((l.i * 100) / l.size) * (p2->r - p1->r)) / 100);
		g = p1->g + ((((l.i * 100) / l.size) * (p2->g - p1->g)) / 100);
		b = p1->b + ((((l.i * 100) / l.size) * (p2->b - p1->b)) / 100);
	}
	else
	{
		r = p1->r;
		g = p1->g;
		b = p1->b;
	}
	return ((r * 256 * 256) + (g * 256) + b);
}

void	plot_line(t_data *data, t_point *p1, t_point *p2)
{
	t_line	l;

	l = bresenham_init(p1, p2);
	while (1)
	{
		if (l.x > 0 && l.x < WIN_X && l.y > 0 && l.y < WIN_Y)
			my_mlx_pixel_put(data, l.x, l.y, get_color(l, p1, p2));
		if (l.x == p2->i && l.y == p2->j)
			break ;
		l.e2 = 2 * l.err;
		if (l.e2 >= l.dy)
		{
			l.err += l.dy;
			l.x += l.sx;
		}
		if (l.e2 <= l.dx)
		{
			l.err += l.dx;
			l.y += l.sy;
		}
		l.i++;
	}
}
