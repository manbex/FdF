/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:22:20 by mbenicho          #+#    #+#             */
/*   Updated: 2022/09/07 15:53:35 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;
	int	sign;

	i = 0;
	n = 0;
	sign = 1;
	if (nptr[i] == '-')
	{
		i++;
		sign = -1;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = (n * 10) + nptr[i] - '0';
		i++;
	}
	return (n * sign);
}

static int	ft_convert(char c)
{
	int	i;

	i = 0;
	while (c != "0123456789abcdef"[i] && c != "0123456789ABCDEF"[i])
		i++;
	return (i);
}

int	ft_atoi_hex(char c1, char c2)
{
	int	n;

	n = 0;
	n = ((ft_convert(c1)) * 16) + ft_convert(c2);
	return (n);
}
