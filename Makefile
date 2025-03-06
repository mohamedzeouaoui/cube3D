
CC = cc
CFLAGS = #-Werror -Wextra -Wall #-fsanitize=address
RM = rm -rf
UTILS = error.c

PARSING = parsing.c check_map.c ft_substr_parsing.c

RAYCASTING = raycaster.c raycaster_utils.c mini_map.c mlx_hooks.c directions.c

CFILES = main.c  ${PARSING} ${UTILS} ${RAYCASTING}
OFILES = ${CFILES:.c=.o}
NAME = cub3D

MLX = -lmlx -lX11 -lXext -lm

LIBFT = -Llibft -lft

all : ${NAME}

${NAME} : ${OFILES}
	${CC} ${CFLAGS} ${OFILES} -o ${NAME} ${MLX} ${LIBFT}

%.o: %.c
	${CC} -c ${CFLAGS} $< -o $@

clean :
	${RM} ${OFILES}

fclean : clean
	${RM} ${NAME}

re : fclean all
