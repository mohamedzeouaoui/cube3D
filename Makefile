
CC = cc
CFLAGS = -Werror -Wextra -Wall #-fsanitize=address
RM = rm -rf
UTILS = ./utils/ft_strlen.c ./utils/print_function.c ./utils/ft_isdigit.c ./utils/ft_strdup.c ./utils/ft_substr_parsing.c \
		./utils/ft_atoi.c ./utils/ft_split.c 

PARSING = ./parsing/parsing.c ./parsing/pars_texture.c ./parsing/pars_color.c ./parsing/check_map.c

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
