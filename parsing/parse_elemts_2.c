/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elemts_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onajem <onajem@student.42.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:45:43 by onajem            #+#    #+#             */
/*   Updated: 2025/07/04 17:07:14 by onajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	line_empty(char *str)
{
	int	i;

	i = 0;
	if (str[0] == 0)
		return (1);
	while (str[i])
	{
		if (!ft_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_dash(char *line)
{
	int	i;
	int	count;

	if (!line)
		return (0);
	count = 0;
	i = 0;
	while (line [i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count == 2)
		return (1);
	return (0);
}

int	parse_cord(char *line, t_game *data)
{
	char	**splited;

	splited = split_space(line);
	if (!splited)
		return (0);
	if (size_2d(splited) > 2 || !init_cordination(splited, data))
		exit_error(splited);
	free_array(splited);
	return (1);
}

int	color_process(char *line, t_game *data)
{
	char	**splited;

	if (!check_dash(line))
		return (0);
	splited = split_space(line);
	if (!splited)
		return (0);
	if (size_2d(splited) > 2 || !init_colors(splited, data))
		exit_error(splited);
	free_array(splited);
	return (1);
}

int	check_args(char *line, t_game *data, int done)
{
	if (!done && (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
			|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)))
	{
		if (!parse_cord(line, data))
			return (0);
	}
	else if (!done && (!ft_strncmp(line, "F ", 2)
			|| !ft_strncmp(line, "C ", 2)))
	{
		if (!color_process(line, data))
			return (0);
	}
	else if (!line_empty(line))
	{
		if (map_begin(line) && done)
			return (2);
		else
			return (0);
	}
	else if (!done && map_begin(line))
		return (0);
	return (1);
}
