
CC = cc
CFLAGS = -Werror -Wextra -Wall 
RM = rm -rf
UTILS = ./utils/ft_strlen.c ./utils/print_function.c ./utils/ft_isdigit.c ./utils/ft_strdup.c

PARSING = ./parsing/parsing.c

GET_NEXT_LINE = ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c

#EXECUTION = 
CFILES = main.c  ${PARSING} ${UTILS} ${GET_NEXT_LINE}
OFILES = ${CFILES:.c=.o}
NAME = cub3D

all : ${NAME}

${NAME} : ${OFILES}
	${CC} ${CFLAGS} ${OFILES} -o ${NAME}

%.o: %.c
	${CC} -c ${CFLAGS} $< -o $@

clean :
	${RM} ${OFILES}

fclean : clean
	${RM} ${NAME}

re : fclean all
