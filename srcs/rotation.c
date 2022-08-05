#include "fdf.h"

void	rotation_x(t_point *p, double a)
{
	double	y;
	double	z;

	y = p->py;
	z = p->pz;
	p->py = (y * cos(a)) - (z * sin(a));
	p->pz = (y * sin(a)) + (z * cos(a));
}

void	rotation_y(t_point *p, double a)
{
	double	x;
	double	z;

	x = p->px;
	z = p->pz;
	p->px = (x * cos(a)) + (z * sin(a));
	p->pz = (z * cos(a)) - (x * sin(a));
}

void	rotation_z(t_point *p, double a)
{
	double	x;
	double	y;

	x = p->px;
	y = p->py;
	p->px = (x * cos(a)) - (y * sin(a));
	p->py = (x * sin(a)) + (y * cos(a));
}
