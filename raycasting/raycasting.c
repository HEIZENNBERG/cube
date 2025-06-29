/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:24:20 by aelkadir          #+#    #+#             */
/*   Updated: 2025/06/29 20:28:54 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static void	dda(t_ray *r, t_game *g)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if ((*r).sideDistX < (*r).sideDistY)
		{
			(*r).sideDistX += (*r).deltaDistX;
			(*r).mapX += (*r).stepX;
			(*r).side = 0;
		}
		else
		{
			(*r).sideDistY += (*r).deltaDistY;
			(*r).mapY += (*r).stepY;
			(*r).side = 1;
		}
		if (g->map[(*r).mapY][(*r).mapX] == '1')
			hit = 1;
	}
}

static void	init_ray(t_ray *r, t_game *g)
{
	(*r).cameraX = 2 * (*r).x / (double)SCREEN_WIDTH - 1;
	(*r).rayDirX = g->player.dirX + g->player.planeX * (*r).cameraX;
	(*r).rayDirY = g->player.dirY + g->player.planeY * (*r).cameraX;
	(*r).mapX = (int)g->player.posX;
	(*r).mapY = (int)g->player.posY;
	(*r).deltaDistX = fabs(1 / (*r).rayDirX);
	(*r).deltaDistY = fabs(1 / (*r).rayDirY);
	(*r).stepX = -((*r).rayDirX < 0) + ((*r).rayDirX >= 0);
	(*r).sideDistX = ((*r).rayDirX < 0) * ((g->player.posX - (*r).mapX)
			* (*r).deltaDistX) + ((*r).rayDirX >= 0)
		* ((*r).sideDistX = ((*r).mapX + 1.0 - g->player.posX)
			* (*r).deltaDistX);
	(*r).stepY = -((*r).rayDirY < 0) + ((*r).rayDirY >= 0);
	(*r).sideDistY = ((*r).rayDirY < 0) * ((g->player.posY - (*r).mapY)
			* (*r).deltaDistY) + ((*r).rayDirY >= 0) * (((*r).mapY + 1.0
				- g->player.posY) * (*r).deltaDistY);
}

static void	raycaster(t_game *g)
{
	t_ray	r;

	r.x = 0;
	while (r.x < SCREEN_WIDTH)
	{
		init_ray(&r, g);
		dda(&r, g);
		r.perpWallDist = (r.side == 0) * (r.sideDistX - r.deltaDistX)
			+ (r.side == 1) * (r.sideDistY - r.deltaDistY);
		r.lineHeight = (int)(SCREEN_HEIGHT / r.perpWallDist);
		r.drawStart = -r.lineHeight / 2 + SCREEN_HEIGHT / 2;
		r.drawEnd = r.lineHeight / 2 + SCREEN_HEIGHT / 2;
		r.texNum = (r.side == 0) * (r.rayDirX <= 0) + (r.side == 1)
			* ((r.rayDirY > 0) * 2 + (r.rayDirY <= 0) * 3);
		r.wallX = (r.side == 0) * (g->player.posY + r.perpWallDist * r.rayDirY)
			+ (r.side == 1) * (g->player.posX + r.perpWallDist * r.rayDirX);
		r.wallX -= floor(r.wallX);
		r.texX = (int)(r.wallX * (double)TEX_WIDTH);
		if ((r.side == 0 && r.rayDirX > 0) || (r.side == 1 && r.rayDirY < 0))
			r.texX = TEX_WIDTH - r.texX - 1;
		draw_ceiling(g, &r);
		draw_wall(g, &r);
		draw_floor(g, r.x, r.drawEnd);
		r.x++;
	}
}

int	render(void *p)
{
	t_game *g;

	g = (t_game *)p;
	move_player(g);
	raycaster(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	return (0);
}
