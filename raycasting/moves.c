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
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = g->player.dirX;
	g->player.dirX = g->player.dirX * cos(angle) - g->player.dirY * sin(angle);
	g->player.dirY = oldDirX * sin(angle) + g->player.dirY * cos(angle);
	oldPlaneX = g->player.planeX;
	g->player.planeX = g->player.planeX * cos(angle) - g->player.planeY
		* sin(angle);
	g->player.planeY = oldPlaneX * sin(angle) + g->player.planeY * cos(angle);
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