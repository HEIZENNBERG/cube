/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:24:23 by aelkadir          #+#    #+#             */
/*   Updated: 2025/07/02 00:26:36 by aelkadir         ###   ########.fr       */
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
		put_pixel_to_img(g, r->x, y, 0x87CEEB);
		y++;
	}
}

void	draw_floor(t_game *g, int x, int draw_end)
{
	int	y;

	y = draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		put_pixel_to_img(g, x, y, 0x228B22);
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

	tex = &g->textures[r->texNum];
	y = r->drawStart;
	if (r->drawEnd >= SCREEN_HEIGHT)
		r->drawEnd = SCREEN_HEIGHT - 1;
	// while (y <= r->drawEnd)
	// {
	// 	d = y * 256 - SCREEN_HEIGHT * 128 + r->lineHeight * 128;
	// 	tex_y = ((d * TEX_HEIGHT) / r->lineHeight) / 256;
	// 	if (tex_y < 0)
	// 		tex_y = 0;
	// 	if (tex_y >= TEX_HEIGHT)
	// 		tex_y = TEX_HEIGHT - 1;
	// 	color = *(int *)(tex->addr + (tex_y * tex->size_line + r->texX
	// 				* (tex->bpp / 8)));
	// 	put_pixel_to_img(g, r->x, y, color);
	// 	y++;
	// }


	double step = (double)TEX_HEIGHT / (double)r->lineHeight;
	double texPos = (r->drawStart - SCREEN_HEIGHT / 2.0 + r->lineHeight / 2.0) * step;

	y = r->drawStart;
	while (y <= r->drawEnd)
	{
		int texY = (int)texPos;
		if (texY < 0)
			texY = 0;
		if (texY >= TEX_HEIGHT)
			texY = TEX_HEIGHT - 1;

		int color = *(unsigned int *)(tex->addr + (texY * tex->size_line + r->texX * (tex->bpp / 8)));
		put_pixel_to_img(g, r->x, y, color);

		texPos += step;
		y++;
	}

}
