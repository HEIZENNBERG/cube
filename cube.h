

#ifndef CUBE_H
#define CUBE_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
# include <limits.h>


typedef struct s_data
{
    int fd_no;
    int fd_so;
    int fd_we;
    int fd_ea;
    int floor;
    int cellin;
    char **map;
    int map_height;
}t_data;

int	ft_space(int ch);
int	valid_color(int val);
void copy_old_lines(char **dest, char **src, int count);
void	exit_error(char **arr);
int fill_elements(char *line, t_data *data, int *done);
void	remove_new_line(char *line);
void	copy_map(char	**tmp, t_data *data, char *line);
void	store_map(char *line, int fd, t_data *data);
int	check_chars(char **arr);
int	check_borders(char **map);
int	check_args_init(t_data *data);
int	init_colors(char **src, t_data *data);

int	validate_map(t_data *data);
int	init_cordination(char **src, t_data *data);
int	parse_color(char **arr);
int	map_begin(char *str);

int	check_args(char *line, t_data *data, int done);
int is_flooded(char c);
int check_flood(char **map, int height);
int	check_lines_overflow(char **map, int height, int i);

int color_process(char *line, t_data *data);
int	parse_cord(char *line, t_data *data);
int	check_dash(char *line);
int	line_empty(char *str);
int is_player_char(char c);
int is_map_char(char c);
int	ft_atoi(const char *nptr);
char	**ft_split(char const *s, char c);
int ft_space(int ch);
char	**split_space(char const *s);
void	*free_array(char **s);
int	size_2d(char **arr);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s1);
void	freee(char **p);
char	*get_left(char *left);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(const char *s, int c);
char	*get_next_line(int fd);


#endif