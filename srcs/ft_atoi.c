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

int	ft_superatoi(char *nptr, int *res)
{
	long	n;
	int	sign;
	int	nb;

	n = 0;
	sign = 1;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = (n * 10);
		if (nb / 10 != n)
			return (1);
		n = (long)nb + *nptr - '0';
		if (n * sign > INT_MAX || n * sign < INT_MIN)
			return (1);
		nptr++;
	}
	*res = n * sign;
	return (0);
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
