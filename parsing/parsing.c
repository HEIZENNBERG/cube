#include "../cube.h"

int init_cordination(char **src, t_data *data)
{
    if (!ft_strncmp(src[0], "NO ", 4))
    {
        data->fd_no = open(src[1], O_RDONLY);
        if (data->fd_no < 0)
            return (0);
    }
    if (!ft_strncmp(src[0], "SO ", 4))
    {
        data->fd_so = open(src[1], O_RDONLY);
        if (data->fd_no < 0)
            return (0);
    }
    if (!ft_strncmp(src[0], "WE ", 4))
    {
        data->fd_no = open(src[1], O_RDONLY);
        if (data->fd_we < 0)
            return (0);
    }
    if (!ft_strncmp(src[0], "EA ", 4))
    {
        data->fd_ea = open(src[1], O_RDONLY);
        if (data->fd_no < 0)
            return (0);
    }
    return (1);
}

void init_colors(char **src, t_data *data)
{
    
}

int check_args(char *line, t_data *data)
{
    int args;
    char **splited;

    args = 0;
    if (!line)
        return (0);
    if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "WE ", 3) 
        || !ft_strncmp(line, "EA ", 3))
    {
        splited = ft_split(line);
        if (!splited)
            return (0);
        if (size_2d(splited) >= 2)
        {
            printf("Error\n");
            free_array(splited);
            return (0);
        }
        return(init_cordination(splited, data));
    }
    else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
    {

    }
    return (1);
}


void init_data(t_data *data, char *file)
{
    int fd;
    char *line;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        printf("Error : input file error\n");
        exit(1);
    }
    while (1)
    {
        line = get_next_line(fd);
        if (!line || check_args(line , data) == 0)
            break;
    }
}

int main(int ac, char *av[])
{
    if (ac != 2)
        return (1);
    t_data *data;
    init_data(data, av[1]);
}