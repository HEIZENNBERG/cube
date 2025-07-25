/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onajem <onajem@student.42.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:24:28 by aelkadir          #+#    #+#             */
/*   Updated: 2025/07/02 20:26:27 by onajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	put_pixel_to_img(t_game *g, int x, int y, int color)
{
	int	offset;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		offset = (y * g->size_line) + (x * (g->bpp / 8));
		*(unsigned int *)(g->img_data + offset) = color;
	}
}

void	load_texture(t_game *g, int i, char *path)
{
	int	tw;
	int	th;

	tw = TEX_WIDTH;
	th = TEX_HEIGHT;
	g->textures[i].img = mlx_xpm_file_to_image(g->mlx, path, &tw, &th);
	if (!g->textures[i].img)
	{
		perror("Error: failed to load a texture\n");
		exit(EXIT_FAILURE);
	}
	g->textures[i].addr = mlx_get_data_addr(g->textures[i].img,
			&g->textures[i].bpp, &g->textures[i].size_line,
			&g->textures[i].endian);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 119)
		game->forward = 1;
	if (keycode == 115)
		game->backward = 1;
	if (keycode == 100)
		game->rotate_left = 1;
	if (keycode == 97)
		game->rotate_right = 1;
	if (keycode == 65307)
		exit(0);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 119)
		game->forward = 0;
	if (keycode == 115)
		game->backward = 0;
	if (keycode == 100)
		game->rotate_left = 0;
	if (keycode == 97)
		game->rotate_right = 0;
	return (0);
}
