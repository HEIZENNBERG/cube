SRC = parsing/utils/get_next_line.c parsing/utils/get_next_line_utils.c parsing/utils/ft_split.c \
  parsing/utils/helpers.c parsing/parsing.c  parsing/utils/split_space.c parsing/utils/ft_atoi.c 


OBJ = ${SRC:.c=.o}

OBJ_B = ${SRC_B:.c=.o}

CC = cc

NAME = cube

RM = rm -f

GFLAGS = 

all : ${NAME}

%.o: %.c cube.h 
	${CC} -fsanitize=address ${GFLAGS} -c $< -o $@ 

${NAME} : ${OBJ}
	${CC} -fsanitize=address ${OBJ} -o ${NAME}

clean : 
	${RM} ${OBJ} 

fclean : clean
	${RM} ${NAME} 

re : fclean all

.PHONY: clean fclean all