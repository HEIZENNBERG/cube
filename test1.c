// cube3d_minimal_raycaster.c
#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

char			*worldMap[] = {
                "1111111111111111111111111",
				"1000000000110000000000001",
                "1011000001110000000000001",
				"1001000000000000000000001",
                "1111111110110000011100001",
				"1000000000110000011101111",
                 "111101111111110111000001",
				"111101111111110111010101",
                 "110000001101010111000001",
				 "100000000000000011000001",
                 "100000001000000011010101",
				"110000011010101111101111", "111101111110101101111101",
				"111111111111111111111111", NULL};

typedef struct s_player
{
	double posX;
    double posY;
	double dirX;
    double dirY;
	double planeX;
    double planeY;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void *img;      
	char *img_data;
	int bpp;
    int size_line;
    int endian;
	t_player	player;
	char		**map;
	int forward, backward, rotate_left, rotate_right;
}				t_game;

void	put_pixel_to_img( t_game *g,int x, int y, int color)
{
	int	offset;

	offset = (y * g->size_line) + (x * (g->bpp / 8));
	*(unsigned int *)(g->img_data + offset) = color;
}

int	key_press(int keycode, t_game *game)
{
	printf("Key pressed: %d\n", keycode);
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

void	move_player(t_game *g)
{
	double	speed;
    double  rot;
	double	angle;
	double	oldDirX;
	double	oldPlaneX;

	speed = 0.01;
    rot = 0.01;
	if (g->forward)
	{
		if (g->map[(int)(g->player.posY)][(int)(g->player.posX + g->player.dirX
				* speed)] != '1')
			g->player.posX += g->player.dirX * speed;
		if (g->map[(int)(g->player.posY + g->player.dirY
				* speed)][(int)(g->player.posX)] != '1')
			g->player.posY += g->player.dirY * speed;
	}
	if (g->backward)
	{
		if (g->map[(int)(g->player.posY)][(int)(g->player.posX - g->player.dirX
				* speed)] != '1')
			g->player.posX -= g->player.dirX * speed;
		if (g->map[(int)(g->player.posY - g->player.dirY
				* speed)][(int)(g->player.posX)] != '1')
			g->player.posY -= g->player.dirY * speed;
	}
	if (g->rotate_left || g->rotate_right)
	{
		angle = g->rotate_left * -rot + !(g->rotate_left)*rot;
		oldDirX = g->player.dirX;
		g->player.dirX = g->player.dirX * cos(angle) - g->player.dirY
			* sin(angle);
		g->player.dirY = oldDirX * sin(angle) + g->player.dirY * cos(angle);
		oldPlaneX = g->player.planeX;
		g->player.planeX = g->player.planeX * cos(angle) - g->player.planeY
			* sin(angle);
		g->player.planeY = oldPlaneX * sin(angle) + g->player.planeY
			* cos(angle);
	}
}

void	raycaster(t_game *g)
{
	int		x;
	int		hit;
	int		side;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	deltaDistX;
	double	deltaDistY;
	int		stepX;
	int		stepY;
	double	sideDistX;
	double	sideDistY;
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;
	int		y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
		rayDirX = g->player.dirX + g->player.planeX *cameraX;
		rayDirY = g->player.dirY + g->player.planeY *cameraX;
		mapX = (int)g->player.posX;
		mapY = (int)g->player.posY;
		deltaDistX = (1 / fabs(rayDirX));
		deltaDistY = fabs(1 / rayDirY);
		stepX = -(rayDirX < 0) + (rayDirX > 0)+0;
		stepY = -(rayDirY < 0) + (rayDirY>0)+0;


		sideDistX = (rayDirX < 0) * (g->player.posX - mapX) * deltaDistX + (rayDirX >= 0)*(mapX
				+ 1.0 - g->player.posX) * deltaDistX;
		sideDistY = (rayDirY < 0) ? ((g->player.posY - mapY) * deltaDistY) :(mapY
				+ 1.0 - g->player.posY) * deltaDistY;
        // sideDistY = (rayDirY < 0) * ((g->player.posY - mapY) * deltaDistY) + (rayDirY > 0)*((mapY
		// 		+ 1.0 - g->player.posY) * deltaDistY);
		hit = 0;
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapY][mapX] == '1')
				hit = 1;
		}
        if(side == 0)
		    perpWallDist = sideDistX -deltaDistX;
        else 
            perpWallDist = sideDistY -deltaDistY;
		lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
		drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;
		color = (side == 0) * 0xFF0000 +(side!=0) *0x880000;
		y = 0;
		while (y < drawStart)
		{
			put_pixel_to_img(g, x, y, 0x87CEEB);
			y++;
		}
		y = drawStart;
		while (y <= drawEnd)
		{
			put_pixel_to_img(g, x, y, color);
			y++;
		}
		y = drawEnd + 1;
		while (y < SCREEN_HEIGHT)
		{
			put_pixel_to_img(g, x, y, 0x228B22);
			y++;
		}
		x++;
	}
}

int	render(void *p)
{
	t_game	*g;

	g = (t_game *)p;
	move_player(g);
	raycaster(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_game g;
	g.map = worldMap;
	g.forward = g.backward = g.rotate_left = g.rotate_right = 0;
	g.player.posX = 11;
	g.player.posY = 10;
	g.player.dirX = -1;
	g.player.dirY = 0,1;
	g.player.planeX = 0;
	g.player.planeY = 0.66;
	g.mlx = mlx_init();
	g.win = mlx_new_window(g.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cube3D");
	g.img = mlx_new_image(g.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	g.img_data = mlx_get_data_addr(g.img, &g.bpp, &g.size_line, &g.endian);

	mlx_loop_hook(g.mlx, render, &g);
	mlx_hook(g.win, 2, 1L << 0, key_press, &g);
	mlx_hook(g.win, 3, 1L << 1, key_release, &g);
	mlx_loop(g.mlx);
	return (0);
}

// cc -fsanitize=address -g test2.c -Imlx -Lmlx -lmlx -lXext -lX11 -lm && ./a.out
