/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onajem <onajem@student.42.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:53:13 by onajem            #+#    #+#             */
/*   Updated: 2025/06/30 17:42:39 by onajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	exit_error(char **arr)
{
	if (arr)
		free_array(arr);
	printf("Error\n");
	exit(1);
}

int	valid_color(int val)
{
	if (val < 0 || val > 255)
		return (0);
	return (1);
}

void	copy_old_lines(char **dest, char **src, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		dest[i] = src[i];
		i++;
	}
}

void	init_data(t_data *data, char *file)
{
	int		fd;
	char	*line;
	int		done;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		(printf("Error\n"), exit(1));
	done = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (fill_elements(line, data, &done) == 0)
			break ;
	}
	store_map(line, fd, data);
	if (!validate_map(data))
		exit_error(data->map);
}

void	pre_init(t_data *data)
{
	data->cellin = -1;
	data->floor = -1;
	data->fd_ea = -1;
	data->fd_no = -1;
	data->fd_we = -1;
	data->fd_so = -1;
	data->x_player = 0;
	data->y_player = 0;
	data->map = NULL;
	data->map_height = 0;
}

#include <string.h>

int main(int ac, char *av[])
{
	if (ac != 2)
		return (1);
	t_data data;
	pre_init(&data);
	init_data(&data, av[1]);
	// int i = 0;
	// while (data.map[i])
	// {
	//     // if (strchr(data.map[i], '\n'))
	//     //     printf("nwl[%d]\n", i);
	//     printf("%s\n", data.map[i]);
	//     i++;
	// }
	// printf("%d | %d\n", data.x_player, data.y_player);
	free_array(data.map);
	// printf("floor : %d | cellin : %d\n", data.floor, data.cellin);
}