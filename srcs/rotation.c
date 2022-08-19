#include "fdf.h"

void	rotation_x(t_point *p, double a)
{
	double	x;
	double	y;
	double	z;

	x = p->px;
	y = p->py;
	z = p->pz;
	p->px = x;
	p->py = (y * cos(a)) - (z * sin(a));
	p->pz = (y * sin(a)) + (z * cos(a));
}

void	rotation_y(t_point *p, double a)
{
	double	x;
	double	y;
	double	z;

	x = p->px;
	y = p->py;
	z = p->pz;
	p->px = (x * cos(a)) + (z * sin(a));
	p->py = y;
	p->pz = (z * cos(a)) - (x * sin(a));
}

void	rotation_z(t_point *p, double a)
{
	double	x;
	double	y;
	double	z;

	x = p->px;
	y = p->py;
	z = p->pz;
	p->px = (x * cos(a)) - (y * sin(a));
	p->py = (x * sin(a)) + (y * cos(a));
	p->pz = z;
}
