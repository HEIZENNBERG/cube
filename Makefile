SRC = parsing/utils/get_next_line.c parsing/utils/get_next_line_utils.c parsing/utils/ft_split.c parsing/utils/error_utils.c \
  parsing/utils/helpers.c parsing/parsing.c parsing/utils/split_space.c parsing/utils/ft_atoi.c \
  parsing/parse_elemts_2.c parsing/parse_elemts.c parsing/parse_map.c parsing/parse_utils.c \
  raycasting/draw.c main.c raycasting/moves.c raycasting/raycasting.c raycasting/utils.c

OBJ = ${SRC:.c=.o}
CC = cc
CFLAGS = -Imlx -fsanitize=address
LDFLAGS = -Lmlx -lmlx -lXext -lX11 -lm
NAME = cube3D
RM = rm -f

MLX_DIR = mlx
MLX_LIB = mlx/libmlx_Linux.a

all: ${NAME}

%.o: %.c cube.h
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJ} ${MLX_LIB}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME} ${LDFLAGS}

${MLX_LIB}:
	$(MAKE) -C ${MLX_DIR}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
