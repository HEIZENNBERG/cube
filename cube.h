

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