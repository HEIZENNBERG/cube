/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:24:23 by aelkadir          #+#    #+#             */
/*   Updated: 2025/07/05 12:47:26 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	draw_ceiling(t_game *g, t_ray *r)
{
	int	y;

	y = 0;
	if (r->texX < 0 || r->texX >= TEX_WIDTH)
		r->texX = 0 * (r->texX < 0) + (r->texX >= TEX_WIDTH) * (TEX_WIDTH - 1);
	if (r->drawStart < 0)
		r->drawStart = 0;
	while (y < r->drawStart)
	{
		put_pixel_to_img(g, r->x, y, g->ceiling);
		y++;
	}
}

void	draw_floor(t_game *g, int x, int draw_end)
{
	int	y;

	y = draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		put_pixel_to_img(g, x, y, g->floor);
		y++;
	}
}

void	draw_wall(t_game *g, t_ray *r)
{
	int			y;
	int			d;
	int			tex_y;
	t_texture	*tex;
	int			color;
	double		step;
	double		text_pos;
	int			texY;

	tex = &g->textures[r->texNum];
	y = r->drawStart;
	if (r->drawEnd >= SCREEN_HEIGHT)
		r->drawEnd = SCREEN_HEIGHT - 1;
	step = (double)TEX_HEIGHT / (double)r->lineHeight;
	text_pos = (r->drawStart - SCREEN_HEIGHT / 2.0 + r->lineHeight / 2.0) * step;
	while (y <= r->drawEnd)
	{
		texY = (int)text_pos;
		if (texY < 0)
			texY = 0;
		if (texY >= TEX_HEIGHT)
			texY = TEX_HEIGHT - 1;
		color = *(unsigned int *)(tex->addr + (texY * tex->size_line + r->texX
					* (tex->bpp / 8)));
		put_pixel_to_img(g, r->x, y++, color);
		text_pos += step;
	}
}
