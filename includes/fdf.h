/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:23:52 by mbenicho          #+#    #+#             */
/*   Updated: 2022/07/12 15:24:23 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define BUFFER_SIZE 4092
# define ZOOM 1.1
# define ANGLE 0.10472
# define WIN_X 1920
# define WIN_Y 1080
# define TRANS 20

# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>

# include <stdio.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		length;
	int		endian;
}	t_data;

typedef struct s_point
{
	double			x;
	double			y;
	double			z;
	double			px;
	double			py;
	double			pz;
	int				i;
	int				j;
	int				r;
	int				g;
	int				b;
	int				show;
	struct s_point *next;
}	t_point;

typedef struct s_list
{
	t_point *p;
	struct s_list *next;
}	t_list;

typedef struct s_vars
{
	t_list	*p;
	t_data	d;
	void	*mlx;
	void	*win;
	double	x_angle;
	double	y_angle;
	double	z_angle;
	int		x_off;
	int		y_off;
	int		x_max;
	int		y_max;
	double		length;
	double	z_size;
	int		exit_code;
}	t_vars;

typedef struct s_line
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	i;
	int	size;

}	t_line;

int		ft_strlen(char	*s);
void	ft_lstfree(t_list *lst);
void	ft_lstadd_back(t_point **lst, t_point *new);
void	ft_lstadd_back1(t_list **lst, t_list *new);
char	*ft_free(char *str);
void	ft_free_tab(char **tab);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *nptr);
int		ft_atoi_hex(char c1, char c2);
char	*ft_strjoin(char *s1, char *s2);
int		get_next_line(int fd, char **str);
int		init(char *file, t_vars *v);
int		parse_line(t_point *new, char *str);
void	plot_line(t_data *data, t_point *p1, t_point *p2);
void	my_mlx_pixel_put(t_data *d, int x, int y, int color);
void	rotation_x(t_point *p, double a);
void	rotation_y(t_point *p, double a);
void	rotation_z(t_point *p, double a);

#endif
