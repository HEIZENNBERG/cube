/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onajem <onajem@student.42.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:51:21 by onajem            #+#    #+#             */
/*   Updated: 2025/07/04 17:19:49 by onajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	remove_new_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			return ;
		}
		i++;
	}
}

void	copy_map(char	**tmp, t_game *data, char *line)
{
	copy_old_lines(tmp, data->map, data->map_height);
	tmp[data->map_height] = line;
	tmp[data->map_height + 1] = NULL;
	free(data->map);
	data->map = tmp;
	data->map_height++;
}

void	store_map(char *line, int fd, t_game *data)
{
	char	**tmp;

	data->map_height = 1;
	data->map = (char **)malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
		(free(line), exit_error(NULL));
	data->map[0] = line;
	data->map[1] = NULL;
	remove_new_line(line);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		remove_new_line(line);
		tmp = (char **)malloc(sizeof(char *) * (data->map_height + 2));
		if (!tmp)
		{
			free(line);
			exit_error(data->map);
		}
		copy_map(tmp, data, line);
	}
}

int	check_chars(char **arr)
{
	int	i;
	int	j;
	int	player;

	if (!arr)
		return (0);
	i = -1;
	player = 0;
	while (arr[++i])
	{
		j = 0;
		if (line_empty(arr[i]))
			return (0);
		while (arr[i][j] && arr[i][j] != 10)
		{
			if (is_map_char(arr[i][j]) == 0 || player > 1)
				return (0);
			if (is_player_char(arr[i][j]))
				player++;
			j++;
		}
	}
	if (player == 0)
		return (0);
	return (1);
}

int	check_borders(char **map)
{
	int	i;
	int	j;

	if (!map)
		return (0);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] != '1')
			return (0);
		j = ft_strlen(map[i]) - 1;
		while (j >= 0 && (map[i][j] == ' ' || map[i][j] == '\n'))
			j--;
		if (j >= 0 && map[i][j] != '1')
			return (0);
		i++;
	}
	if (map[i - 1] && !map_begin(map[i - 1]))
		return (0);
	return (1);
}
