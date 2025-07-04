/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onajem <onajem@student.42.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:24:18 by aelkadir          #+#    #+#             */
/*   Updated: 2025/07/01 16:02:10 by onajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

char	*worldMap[] = {"1111111111111111111111111", "1000000000110000000000001",
		"1011000001110000000000001", "1001000000000000000000001",
		"1111111110110000011100001", "1000000000110000011101111",
		"111101111111110111000001", "111101111111110111010101",
		"110000001101010111000001", "100000000000000011000001",
		"100000001000000011010101", "110000011000101111101111",
		"111101111110101101111101", "111111111111111111111111", NULL};

int	main(void)
{
	t_game g;

	g.map = worldMap;
	g.forward = 0;
	g.backward = 0;
	g.rotate_left = 0;
	g.rotate_right = 0;
	g.player.posX = 10;
	g.player.posY = 11;
	g.player.dirX = -1;
	g.player.dirY = 0.1;
	g.player.planeX = 0;
	g.player.planeY = 0.66;
	g.mlx = mlx_init();
	load_texture(&g, 0, "textures/no.xpm");
	load_texture(&g, 1, "textures/so.xpm");
	load_texture(&g, 2, "textures/ea.xpm");
	load_texture(&g, 3, "textures/we.xpm");
	g.win = mlx_new_window(g.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cube3D");
	g.img = mlx_new_image(g.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	g.img_data = mlx_get_data_addr(g.img, &g.bpp, &g.size_line, &g.endian);
	mlx_loop_hook(g.mlx, render, &g);
	mlx_hook(g.win, 2, 1L << 0, key_press, &g);
	mlx_hook(g.win, 3, 1L << 1, key_release, &g);
	mlx_loop(g.mlx);
	return (0);
}
