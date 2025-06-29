/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:24:14 by aelkadir          #+#    #+#             */
/*   Updated: 2025/06/29 20:24:15 by aelkadir         ###   ########.fr       */
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
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

typedef struct s_data
{
	int			fd_no;
	int			fd_so;
	int			fd_we;
	int			fd_ea;
	int			floor;
	int			cellin;
	char		**map;
	int			map_height;
}				t_data;

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
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_data;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;
	char		**map;
	int			forward;
	int			backward;
	int			rotate_left;
	int			rotate_right;
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

int				ft_space(int ch);
int				valid_color(int val);
void			copy_old_lines(char **dest, char **src, int count);
void			exit_error(char **arr);
int				fill_elements(char *line, t_data *data, int *done);
void			remove_new_line(char *line);
void			copy_map(char **tmp, t_data *data, char *line);
void			store_map(char *line, int fd, t_data *data);
int				check_chars(char **arr);
int				check_borders(char **map);
int				check_args_init(t_data *data);
int				init_colors(char **src, t_data *data);

int				validate_map(t_data *data);
int				init_cordination(char **src, t_data *data);
int				parse_color(char **arr);
int				map_begin(char *str);

int				check_args(char *line, t_data *data, int done);
int				is_flooded(char c);
int				check_flood(char **map, int height);
int				check_lines_overflow(char **map, int height, int i);

int				color_process(char *line, t_data *data);
int				parse_cord(char *line, t_data *data);
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