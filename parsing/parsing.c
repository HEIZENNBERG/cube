#include "../cube.h"

void exit_error(char **arr)
{
    if (arr)
        free_array(arr);
    printf("Error\n");
    exit(1);
}

int check_args_init(t_data *data)
{
    if (data->cellin == -1)
        return (0);
    if (data->floor == -1)
        return (0);
    if (data->fd_ea == -1)
        return (0);
    if (data->fd_we == -1)
        return (0);
    if (data->fd_so == -1)
        return (0);
    if (data->fd_no == -1)
        return (0);
    return (1); 
}
int init_cordination(char **src, t_data *data)
{
    int fd = open(src[1], O_RDONLY);
    if (fd < 0)
        return (0);

    if (!ft_strncmp(src[0], "NO", 2))
        data->fd_no = fd;
    else if (!ft_strncmp(src[0], "SO", 2))
        data->fd_so = fd;
    else if (!ft_strncmp(src[0], "WE", 2))
        data->fd_we = fd;
    else if (!ft_strncmp(src[0], "EA", 2))
        data->fd_ea = fd;
    else
        return (0);
    return (1);
}


static int	valid_color(int val)
{
	if (val < 0 || val > 255)
		return (0);
	return (1);
}

int	parse_color(char **arr)
{
	int	r;
	int	g;
	int	b;

	if (size_2d(arr) != 3)
		return (-1);
	r = ft_atoi(arr[0]);
	g = ft_atoi(arr[1]);
	b = ft_atoi(arr[2]);
	if (!valid_color(r) || !valid_color(g) || !valid_color(b))
		return (-1);
	return ((r << 16) | (g << 8) | b);
}


int	init_colors(char **src, t_data *data)
{
	char	**arr;
	int		color;

	arr = ft_split(src[1], ',');
	if (!arr || size_2d(arr) != 3)
	{
		free_array(arr);
		return (0);
	}
	color = parse_color(arr);
	free_array(arr);
	if (color == -1)
		return (0);
	if (!ft_strncmp(src[0], "F", 1))
		data->floor = color;
	else if (!ft_strncmp(src[0], "C", 1))
		data->cellin = color;
	else
		return (0);
	return (1);
}

int map_begin(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\n')
    {
        if (str[i] != '1' && str[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

int line_empty(char *str)
{
    int i;

    i = 0;
    if (str[0] == 0)
        return (1);
    while (str[i])
    {
        if (!ft_space(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int check_map(char *line, t_data *data)
{
    if (!line)
        return (0);
    if (!data->map && map_begin(line))
    {
        data->map = (char **) malloc(2 * sizeof(char*));
        if (!data->map)
            return(0);
        data->map[data->map_height] = ft_strdup(line);
        data->map_height++;
        data->map[data->map_height] = NULL;
    }
    return (1);
}

int check_args(char *line, t_data *data, int done)
{
    int args;
    char **splited;

    args = 0;
    if (!line)
        return (0);
    if (!done && (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "WE ", 3) 
        || !ft_strncmp(line, "EA ", 3)))
    {
        splited = split_space(line);
        if (!splited)
            return (0);
        if (size_2d(splited) > 2 || !init_cordination(splited, data))
            exit_error(splited);
        free_array(splited);
    }
    else if (!done && (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2)))
    {
        splited = split_space(line);
        if (!splited)
            return (0);
        if (size_2d(splited) > 2 || !init_colors(splited, data))
            exit_error(splited);
        free_array(splited);
    }
    else if (!done && !line_empty(line) && !map_begin(line))
    {
        printf("yep\n");
        return(0);
    }
    else
    {
        printf("val\n");
        exit(1);
        return (check_map(line, data));
    }
    return (1);
}


void init_data(t_data *data, char *file)
{
    int fd;
    char *line;
    int done;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        printf("Error\n");
        exit(1);
    }
    done = 0;
    while (1)
    {
        line = get_next_line(fd);
        // printf("%s", line);
        if (!line)
            break;
        if (check_args(line , data, done) == 0)
        {
            free(line);
            exit_error(NULL);
        }
        if (check_args_init(data))
            done = 1;
        free(line);
    }
}

void pre_init(t_data *data)
{
    data->cellin = -1;
    data->floor = -1;
    data->fd_ea = -1;
    data->fd_no = -1;
    data->fd_we = -1;
    data->fd_so = -1;
    data->map = NULL;
    data->map_height = 0;
}

int main(int ac, char *av[])
{
    if (ac != 2)
        return (1);
    t_data data;
    pre_init(&data);
    init_data(&data, av[1]);
    free_array(data.map);
    // printf("floor : %d | cellin : %d\n", data.floor, data.cellin);
}