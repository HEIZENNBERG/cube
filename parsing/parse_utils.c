/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onajem <onajem@student.42.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:52:33 by onajem            #+#    #+#             */
/*   Updated: 2025/06/29 15:52:50 by onajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	check_args_init(t_data *data)
{
	if (data->cellin == -1)
		return (0);
	if (data->floor == -1)
		return (0);
	if (data->fd_ea == -1)
		return (0);
	if (data->fd_we == -1)
		return (0);
	if (data->fd_so == -1)
		return (0);
	if (data->fd_no == -1)
		return (0);
	return (1);
}

int	init_cordination(char **src, t_data *data)
{
	int	fd;

	fd = open(src[1], O_RDONLY);
	if (fd < 0)
		return (0);
	if (!ft_strncmp(src[0], "NO", 2))
		data->fd_no = fd;
	else if (!ft_strncmp(src[0], "SO", 2))
		data->fd_so = fd;
	else if (!ft_strncmp(src[0], "WE", 2))
		data->fd_we = fd;
	else if (!ft_strncmp(src[0], "EA", 2))
		data->fd_ea = fd;
	else
		return (0);
	return (1);
}

int	parse_color(char **arr)
{
	int	r;
	int	g;
	int	b;

	if (size_2d(arr) != 3)
		return (-1);
	r = ft_atoi(arr[0]);
	g = ft_atoi(arr[1]);
	b = ft_atoi(arr[2]);
	if (!valid_color(r) || !valid_color(g) || !valid_color(b))
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

int	init_colors(char **src, t_data *data)
{
	char	**arr;
	int		color;

	arr = ft_split(src[1], ',');
	if (!arr || size_2d(arr) != 3)
	{
		free_array(arr);
		return (0);
	}
	color = parse_color(arr);
	free_array(arr);
	if (color == -1)
		return (0);
	if (!ft_strncmp(src[0], "F", 1))
		data->floor = color;
	else if (!ft_strncmp(src[0], "C", 1))
		data->cellin = color;
	else
		return (0);
	return (1);
}

int	map_begin(char *str)
{
	int	i;
	int	has_wall;

	i = 0;
	has_wall = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != '1' && str[i] != ' ')
			return (0);
		if (str[i] == '1')
			has_wall = 1;
		i++;
	}
	return (has_wall);
}
