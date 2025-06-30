/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elemts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onajem <onajem@student.42.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:49:06 by onajem            #+#    #+#             */
/*   Updated: 2025/06/30 17:35:48 by onajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	is_flooded(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	check_flood(char **map, int height)
{
	int	i;
	int	j;

	i = 1;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if (is_flooded(map[i][j]))
			{
				if (map[i - 1][j] == ' ')
					return (0);
				if (map[i + 1][j] && map[i + 1][j] == ' ')
					return (0);
				if (j == 0 || map[i][j - 1] == ' ')
					return (0);
				if (map[i][j + 1] && map[i][j + 1] == ' ')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_lines_overflow(char **map, int height, int i)
{
	int		j;
	int		curr_len;
	int		top_len;
	int		bot_len;
	char	c;

	while (++i < height - 1)
	{
		curr_len = ft_strlen(map[i]);
		top_len = ft_strlen(map[i - 1]);
		bot_len = ft_strlen(map[i + 1]);
		j = 0;
		while (j < curr_len)
		{
			c = map[i][j];
			if (j >= top_len && is_flooded(c))
				return (0);
			if (j >= bot_len && is_flooded(c))
				return (0);
			j++;
		}
	}
	return (1);
}

void	normilize_map(t_data *data)
{
	int	i;
	int	j;
	
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == ' ')
				data->map[i][j] = '0';
			if (is_player_char(data->map[i][j]))
			{
				data->y_player = i;
				data->x_player = j;
				data->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

int	validate_map(t_data *data)
{
	int	i;

	if (!data)
		return (0);
	if (!check_chars(data->map))
		return (0);
	if (!check_borders(data->map))
		return (0);
	i = 0;
	if (!check_lines_overflow(data->map, data->map_height, i))
		return (0);
	if (!check_flood(data->map, data->map_height))
		return (0);
	normilize_map(data);
	return (1);
}

int	fill_elements(char *line, t_data *data, int *done)
{
	int	map_start;	

	map_start = check_args(line, data, *done);
	if (map_start == 0)
	{
		free(line);
		exit_error(NULL);
	}
	else if (map_start == 2)
		return (0);
	if (check_args_init(data))
		*done = 1;
	free(line);
	return (1);
}
