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

/*void	ft_print_list(t_point *list)
{
	while (list)
	{
		printf("{%f, %f, %f} R=%d G=%d B=%d\n", list->x, list->y, list->z, list->r, list->g, list->b);
		list = list->next;
	}
}*/

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
		/*printf("x_angle = %f\ny_angle = %f\nz_angle = %f\n", v.x_angle, v.y_angle, v.z_angle);
		printf("x_max = %d\ny_max = %d\nz_max = %d\n\n", v.x_max, v.y_max, v.z_max);
		ft_print_list(v.p);*/
		return (0);
	}
	return (write(2, "Error\n", 6), 1);
}
