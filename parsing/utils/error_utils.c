/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:27:09 by onajem            #+#    #+#             */
/*   Updated: 2025/07/06 17:31:03 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	p_error(char *err)
{
	printf("Error\n");
	if (err != NULL)
		printf("%s\n", err);
}

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

void	exit_error(char **arr)
{
	if (arr)
		free_array(arr);
	ft_open(NULL, 0);
	exit(1);
}

int	valid_color(int val)
{
	if (val < 0 || val > 255)
		return (0);
	return (1);
}
