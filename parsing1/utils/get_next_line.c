/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onajem <onajem@student.42.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:18:10 by onajem            #+#    #+#             */
/*   Updated: 2025/06/22 17:05:26 by onajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	freee(char **s)
{
	free(*s);
	*s = (NULL);
}

char	*get_left(char *left)
{
	char	*result;
	int		i;

	i = 0;
	if (!left)
		return (NULL);
	while (left[i] && left[i] != '\n')
		i++;
	if (left[i] == '\0')
		return (freee(&left), NULL);
	i++;
	result = ft_strdup(left + i);
	return (freee(&left), result);
}

char	*get__line(char *buff)
{
	char	*dest;
	int		i;
	int		j;

	if (!buff || !*buff)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\0')
		return (ft_strdup(buff));
	i++;
	dest = malloc(i + 1);
	if (!dest)
		return (NULL);
	j = 0;
	while (j < i)
	{
		dest[j] = buff[j];
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*allocate(size_t size)
{
	char	*buf;

	buf = malloc(size + 1);
	if (!buf)
		return (NULL);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*left;
	char		*buf;
	char		*line;
	int			len;

	if (fd < 0)
		return (NULL);
	buf = allocate(10);
	while (1)
	{
		len = read(fd, buf, 10);
		if (len < 0)
			return (freee(&buf), freee(&left), NULL);
		buf[len] = '\0';
		left = ft_strjoin(left, buf);
		if (ft_strchr(left, '\n') || len == 0)
			break ;
	}
	if (!left)
		return (NULL);
	line = get__line(left);
	left = get_left(left);
	return (freee(&buf), line);
}
