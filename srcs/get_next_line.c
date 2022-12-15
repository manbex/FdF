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

char	*ft_customjoin(char *s1, char *s2)
{
	char	*str;
	size_t	size;
	int		i;

	i = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		*s1 = 0;
	}
	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (free(s1), NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (*s2)
		str[i++] = *s2++;
	str[i] = 0;
	return (free(s1), str);
}

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

int	get_line(char *stash, char **line)
{
	char	*str;
	int		size;
	int		i;

	i = 0;
	size = 0;
	if (!stash)
		return (*line = NULL, 0);
	while (stash[size] && stash[size] != '\n')
		size++;
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (free(stash), *line = NULL, 1);
	while (i < size)
	{
		str[i] = stash[i];
		i++;
	}
	str[i] = 0;
	return (*line = str, 0);
}

int	get_stash(char **stash, char **str)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	size = 0;
	if (!*stash)
		return (0);
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i] == '\n')
		i++;
	while ((*stash)[i + size])
		size++;
	if (!size)
		return (free(*stash), *stash = NULL, 0);
	new = malloc((size + 1) * sizeof(char));
	if (!new)
		return (free(*stash), free(*str), 1);
	while ((*stash)[i])
		new[j++] = (*stash)[i++];
	new[j] = 0;
	return (free(*stash), *stash = new, 0);
}

int	get_next_line(int fd, char **str)
{
	char		*buf;
	static char	*stash[1024];
	int			readed;
	char		*line;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (free(stash[fd]), *str = NULL, 1);
	readed = 1;
	while (!ft_have_newline(stash[fd]) && readed)
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed < 0)
			return (free(buf), free(stash[fd]), *str = NULL, 1);
		buf[readed] = 0;
		if (readed)
		{
			stash[fd] = ft_customjoin(stash[fd], buf);
			if (!stash[fd])
				return (free(buf), *str = NULL, 1);
		}
	}
	if (get_line(stash[fd], &line) || get_stash(&stash[fd], &line))
		return (free(buf), *str = NULL, 1);
	return (free(buf), *str = line, 0);
}
