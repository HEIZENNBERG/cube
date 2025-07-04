/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:24:18 by aelkadir          #+#    #+#             */
/*   Updated: 2025/07/04 22:50:53 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static void	load_textures(t_game *g)
{
	load_texture(g, 0, g->textures[0].path);
	load_texture(g, 1, g->textures[1].path);
	load_texture(g, 2, g->textures[2].path);
	load_texture(g, 3, g->textures[3].path);
}

void	free_textures(t_game game)
{
	free(game.textures[0].path);
	free(game.textures[1].path);
	free(game.textures[2].path);
	free(game.textures[3].path);
}

int	main(int ac, char *av[])
{
	t_game	game;

	if (ac != 2)
	{
		printf("Error\nOne input file is required!\n");
		return (1);
	}
	pre_init(&game);
	init_data(&game, av[1]);
	game.player.planeX = -game.player.dirY * FOV;
	game.player.planeY = game.player.dirX * FOV;
	game.mlx = mlx_init();
	load_textures(&game);
	game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cube3D");
	game.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game.img_data = mlx_get_data_addr(game.img, &game.bpp, &game.size_line,
			&game.endian);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_loop(game.mlx);
	free_array(game.map);
	free_textures(game);
	return (0);
}
