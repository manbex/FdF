/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:32:20 by mbenicho          #+#    #+#             */
/*   Updated: 2022/05/16 17:32:21 by mbenicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_have_newline(char *str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i] && str[i] != '\n')
			i++;
		if (str[i] == '\n')
			return (1);
	}
	return (0);
}

char	*get_line(char *stash)
{
	char	*str;
	int		size;
	int		i;

	i = 0;
	size = 0;
	if (!stash)
		return (NULL);
	while (stash[size] && stash[size] != '\n')
		size++;
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (ft_free(stash));
	while (i < size)
	{
		str[i] = stash[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*get_stash(char *stash)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	size = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	while (stash[i + size])
		size++;
	if (!size)
		return (ft_free(stash));
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (ft_free(stash));
	while (stash[i])
		str[j++] = stash[i++];
	str[j] = 0;
	return (free(stash), str);
}

int	get_next_line(int fd, char **str)
{
	char		*buf;
	static char	*stash;
	int			readed;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (ft_free(stash), -1);
	readed = 1;
	while (!ft_have_newline(stash) && readed)
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed < 0)
			return (free(buf), ft_free(stash), -1);
		buf[readed] = 0;
		if (readed)
		{
			stash = ft_strjoin(stash, buf);
			if (!stash)
				return (ft_free(buf), -1);
		}
	}
	*str = get_line(stash);
	stash = get_stash(stash);
	return (free(buf), readed);
}
