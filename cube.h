/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onajem <onajem@student.42.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:24:14 by aelkadir          #+#    #+#             */
/*   Updated: 2025/07/07 12:33:58 by onajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "mlx/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define TEX_WIDTH 480
# define TEX_HEIGHT 480
# define FOV 0.66
# define COLLISION_BUFFER 0.1

typedef struct s_player
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
}				t_player;

typedef struct s_texture
{
	char		*path;
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_texture;

typedef struct s_game
{
	int			floor;
	int			ceiling;

	void		*mlx;
	void		*win;
	void		*img;
	char		*img_data;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;
	int			map_height;
	char		**map;
	int			forward;
	int			backward;
	int			rotate_left;
	int			rotate_right;
	int			left;
	int			right;
	t_texture	textures[4];
}				t_game;

typedef struct s_ray
{
	int			x;
	int			mapX;
	int			mapY;
	int			stepX;
	int			stepY;
	int			side;
	int			lineHeight;
	int drawStart, drawEnd;
	int texX, texNum;

	double		cameraX;
	double rayDirX, rayDirY;
	double deltaDistX, deltaDistY;
	double sideDistX, sideDistY;
	double		perpWallDist;
	double		wallX;
}				t_ray;

void			p_error(char *err);
int				ft_open(char *file, int flag);
int				ft_space(int ch);
int				valid_color(int val);
void			copy_old_lines(char **dest, char **src, int count);
void			exit_error(char **arr);
int				fill_elements(char *line, t_game *data, int *done);
void			remove_new_line(char *line);
void			copy_map(char **tmp, t_game *data, char *line);
void			store_map(char *line, int fd, t_game *data);
int				check_chars(char **arr);
int				check_borders(char **map);
int				init_colors(char **src, t_game *data);
int				check_args_init(t_game *data);
int				validate_map(t_game *data);
int				init_cordination(char **src, t_game *data);
int				parse_color(char **arr);
int				map_begin(char *str);

int				check_args(char *line, t_game *data, int done);
int				is_flooded(char c);
int				check_flood(char **map, int height);
int				check_lines_overflow(char **map, int height, int i);

int				color_process(char *line, t_game *data);
int				parse_cord(char *line, t_game *data);
int				check_dash(char *line);
int				line_empty(char *str);
int				is_player_char(char c);
int				is_map_char(char c);
int				ft_atoi(const char *nptr);
char			**ft_split(char const *s, char c);
int				ft_space(int ch);
char			**split_space(char const *s);
void			*free_array(char **s);
int				size_2d(char **arr);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strrchr(const char *s, int c);
char			*ft_strdup(const char *s1);
void			freee(char **p);
char			*get_left(char *left);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char *s1, char *s2);
int				ft_strchr(const char *s, int c);
void			pre_init(t_game *data);
void			init_data(t_game *data, char *file);
char			*get_next_line(int fd);

// raycasting

void			put_pixel_to_img(t_game *g, int x, int y, int color);
void			load_texture(t_game *g, int i, char *path);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
void			move_player(t_game *g);
void			draw_ceiling(t_game *g, t_ray *r);
void			draw_floor(t_game *g, int x, int draw_end);
void			draw_wall(t_game *g, t_ray *r);
int				render(void *p);
#endif