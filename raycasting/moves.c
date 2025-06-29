/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:24:25 by aelkadir          #+#    #+#             */
/*   Updated: 2025/06/29 20:26:56 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static void	move_forward(t_game *g, double speed)
{
	if (g->map[(int)(g->player.posY)][(int)(g->player.posX + g->player.dirX
			* speed)] != '1')
		g->player.posX += g->player.dirX * speed;
	if (g->map[(int)(g->player.posY + g->player.dirY
			* speed)][(int)(g->player.posX)] != '1')
		g->player.posY += g->player.dirY * speed;
}

static void	move_backward(t_game *g, double speed)
{
	if (g->map[(int)(g->player.posY)][(int)(g->player.posX - g->player.dirX
			* speed)] != '1')
		g->player.posX -= g->player.dirX * speed;
	if (g->map[(int)(g->player.posY - g->player.dirY
			* speed)][(int)(g->player.posX)] != '1')
		g->player.posY -= g->player.dirY * speed;
}

static void	rotate_player(t_game *g, double angle)
{
	double	oldir_x;
	double	oldplane_x;

	oldir_x = g->player.dirX;
	g->player.dirX = g->player.dirX * cos(angle) - g->player.dirY * sin(angle);
	g->player.dirY = oldir_x * sin(angle) + g->player.dirY * cos(angle);
	oldplane_x = g->player.planeX;
	g->player.planeX = g->player.planeX * cos(angle) - g->player.planeY
		* sin(angle);
	g->player.planeY = oldplane_x * sin(angle) + g->player.planeY * cos(angle);
}

void	move_player(t_game *g)
{
	double	speed;
	double	rot;
	double	angle;

	speed = 0.02;
	rot = 0.02;
	if (g->forward)
		move_forward(g, speed);
	if (g->backward)
		move_backward(g, speed);
	if (g->rotate_left || g->rotate_right)
	{
		if (g->rotate_left)
			angle = -rot;
		else
			angle = rot;
		rotate_player(g, angle);
	}
}
