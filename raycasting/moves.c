/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:24:25 by aelkadir          #+#    #+#             */
/*   Updated: 2025/07/06 11:27:48 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static void	move_forward_backward(t_game *g, double speed, int dir)
{
	if (dir)
	{
		if (g->map[(int)(g->player.posY)][(int)(g->player.posX + g->player.dirX
				* (speed + COLLISION_BUFFER))] != '1')
			g->player.posX += g->player.dirX * speed;
		if (g->map[(int)(g->player.posY + g->player.dirY * (speed
					+ COLLISION_BUFFER))][(int)(g->player.posX)] != '1')
			g->player.posY += g->player.dirY * speed;
	}
	else
	{
		if (g->map[(int)(g->player.posY)][(int)(g->player.posX - g->player.dirX
				* speed)] != '1')
			g->player.posX -= g->player.dirX * speed;
		if (g->map[(int)(g->player.posY - g->player.dirY
				* speed)][(int)(g->player.posX)] != '1')
			g->player.posY -= g->player.dirY * speed;
	}
}

static void	move_right_left(t_game *g, double speed, int dir)
{
	if (dir)
	{
		if (g->map[(int)(g->player.posY)][(int)(g->player.posX
				+ g->player.planeX * speed)] != '1')
			g->player.posX += g->player.planeX * speed;
		if (g->map[(int)(g->player.posY + g->player.planeY
				* speed)][(int)(g->player.posX)] != '1')
			g->player.posY += g->player.planeY * speed;
	}
	else
	{
		if (g->map[(int)(g->player.posY)][(int)(g->player.posX
				- g->player.planeX * speed)] != '1')
			g->player.posX -= g->player.planeX * speed;
		if (g->map[(int)(g->player.posY - g->player.planeY
				* speed)][(int)(g->player.posX)] != '1')
			g->player.posY -= g->player.planeY * speed;
	}
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

	speed = 0.02;
	rot = 0.02;
	if (g->forward)
		move_forward_backward(g, speed, 1);
	if (g->backward)
		move_forward_backward(g, speed, 0);
	if (g->right)
		move_right_left(g, speed, 1);
	if (g->left)
		move_right_left(g, speed, 0);
	if (g->rotate_left)
		rotate_player(g, rot);
	if (g->rotate_right)
		rotate_player(g, -rot);
}
