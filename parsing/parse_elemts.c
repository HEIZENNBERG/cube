/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elemts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:49:06 by onajem            #+#    #+#             */
/*   Updated: 2025/07/06 17:30:17 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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

void	init_player_dirc(char c, double *x, double *y)
{
	if (c == 'N')
	{
		*x = 0;
		*y = -1;
	}
	if (c == 'E')
	{
		*x = 1;
		*y = 0;
	}
	if (c == 'S')
	{
		*x = 0;
		*y = 1;
	}
	if (c == 'W')
	{
		*x = -1;
		*y = 0;
	}
}

void	normilize_map(t_game *data)
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
				init_player_dirc(data->map[i][j], &data->player.dirX,
					&data->player.dirY);
				data->player.posY = i + 0.5;
				data->player.posX = j + 0.5;
				data->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

int	validate_map(t_game *data)
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

int	fill_elements(char *line, t_game *data, int *done)
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
