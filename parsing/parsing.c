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
    int i = 0;
    int has_wall = 0;

    while (str[i] && str[i] != '\n')
    {
        if (str[i] != '1' && str[i] != ' ')
            return (0);
        if (str[i] == '1')
            has_wall = 1;
        i++;
    }
    return has_wall; 
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
        {
            exit_error(splited);
        }
        free_array(splited);
    }
    else if (!line_empty(line))
    {
        if (map_begin(line) && done)
            return(2);
        else 
            return (0);
    }
    else if (!done && map_begin(line))
        return (0);
    return (1);
}

void copy_old_lines(char **dest, char **src, int count)
{
    int i = 0;
    while (i < count)
    {
        dest[i] = src[i];
        i++;
    }
}


void store_map(char *line, int fd, t_data *data)
{
    char **tmp;

    data->map_height = 1;
    data->map = (char **)malloc(sizeof(char *) * (data->map_height + 1));
    if (!data->map)
    {
        free(line);
        exit_error(NULL);
    }
    
    data->map[0] = line;
    data->map[1] = NULL;

    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        tmp = (char **)malloc(sizeof(char *) * (data->map_height + 2));
        if (!tmp)
        {
            free(line);
            exit_error(data->map);
        }

        copy_old_lines(tmp, data->map, data->map_height);

        tmp[data->map_height] = line;
        tmp[data->map_height + 1] = NULL;
        free(data->map);

        data->map = tmp;
        data->map_height++;
    }

}


int is_map_char(char c)
{
    return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int is_player_char(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int check_chars(char **arr)
{
    int i;
    int j;
    int player;

    if (!arr)
        return (0);
    i = 0;
    player = 0;
    while (arr[i])
    {
        j = 0;
        if (line_empty(arr[i]))
            return (0);
        while (arr[i][j] && arr[i][j] != 10)
        {
            if (is_map_char(arr[i][j]) == 0 || player > 1)
                return (0);
            if (is_player_char(arr[i][j]))
                player++;
            j++;
        }
        i++;
    }
    return (1);
}

int check_borders(char **map)
{
    int i = 0;
    int j;

    if (!map)
        return (0);

    while (map[i])
    {
        j = 0;

        while (map[i][j] == ' ')
            j++;

        if (map[i][j] != '1')
            return (0);
        

        j = ft_strlen(map[i]) - 1;

        while (j >= 0 && (map[i][j] == ' ' || map[i][j] == '\n'))
            j--;

        if (j >= 0 && map[i][j] != '1')

            return (0);

        i++;
    }
    if (map[i -1 ] && !map_begin(map[i - 1]))
        return (0);
    
    return (1);
}


int is_flooded(char c)
{
    return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int check_flood(char **map, int height)
{
    int i;
    int j;

    i = 1;
    while (i < height)
    {
        j = 0;
        while (map[i][j])
        {
            if (is_flooded(map[i][j]))
            {
                if (map[i - 1][j] == ' ')
                    return (0);
                if (map[i + 1][j] && map[i + 1][j] == ' ')
                    return (0);
                if (j == 0 || map[i][j - 1] == ' ')
                    return (0);
                if (map[i][j + 1] && map[i][j + 1] == ' ')
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1); 
}


int check_lines_overflow(char **map, int height)
{
    int i;
    int j;
    int top_len;
    int bot_len;
    int  curr_len;

    for (i = 1; i < height - 1; i++)
    {
        curr_len = ft_strlen(map[i]);
        top_len = ft_strlen(map[i - 1]);
        bot_len = ft_strlen(map[i + 1]);

        for (j = 0; j < curr_len; j++)
        {
            char c = map[i][j];
            if (j >= top_len && is_flooded(c)) {

                return (0);
            }
            if (j >= bot_len && is_flooded(c)) {

                return (0);
            }
        }
    }
    return (1);
}


int validate_map(t_data *data)
{
    if (!data)
        return (0);
    if (!check_chars(data->map))
        return (0);
    if (!check_borders(data->map))
        return (0);
    if (!check_lines_overflow(data->map, data->map_height))
        return (0);
    if (!check_flood(data->map, data->map_height))
        return (0);
    return (1);
}

void init_data(t_data *data, char *file)
{
    int fd;
    char *line;
    int done;
    int map_start;


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
        if (!line)
            break;
        map_start = check_args(line , data, done);
        if (map_start == 0)
        {
            free(line);
            exit_error(NULL);
        }
        else if (map_start == 2)
            break;
        if (check_args_init(data))
            done = 1;
        free(line);
    }
    store_map(line, fd, data);
    if (!validate_map(data))
    {
        exit_error(data->map);
    }
        // return (0);
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
    // int i = 0;
    // while (data.map[i])
    // {
    //     printf("%s", data.map[i]);
    //     i++;
    // }
    free_array(data.map);
    // printf("floor : %d | cellin : %d\n", data.floor, data.cellin);
}