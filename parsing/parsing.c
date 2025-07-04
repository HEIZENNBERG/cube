/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onajem <onajem@student.42.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:53:13 by onajem            #+#    #+#             */
/*   Updated: 2025/07/04 18:33:05 by onajem           ###   ########.fr       */
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

int ends_with(const char *haystack, const char *needle)
{
    int hay_len;
    int needle_len;
	int res;

	hay_len = ft_strlen(haystack);
    needle_len = ft_strlen(needle);
    if (needle_len > hay_len)
	{
        return (0);
	}
	haystack = haystack + (hay_len - needle_len);
    res = ft_strncmp(haystack, needle, needle_len);
	return (res);
}

void	init_data(t_game *data, char *file)
{
	int		fd;
	char	*line;
	int		done;

	if (ends_with(file, ".cub") != 0)
		(printf("Error\nRequired a .cub file!\n"), exit(1));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		(printf("Error\nFile could not open!\n"), exit(1));
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

void	pre_init(t_game *data)
{
	data->textures[0].path = NULL;
	data->textures[1].path = NULL;
	data->textures[2].path = NULL;
	data->textures[3].path = NULL;
	data->map = NULL;
	data->map_height = 0;
}

#include <string.h>

int main(int ac, char *av[])
{
	if (ac != 2)
	{
		printf("Error\nOne input file is required!\n");
		return (1);
	}
	t_game game; 
	pre_init(&game);
	init_data(&game, av[1]);
	printf("%s\n", game.textures[0].path);
	free_array(game.map);
	free( game.textures[0].path);
	free( game.textures[1].path);
	free( game.textures[2].path);
	free( game.textures[3].path);
}