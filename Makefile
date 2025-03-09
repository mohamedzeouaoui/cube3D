
CC = cc
CFLAGS = #-Werror -Wextra -Wall #-fsanitize=address
RM = rm -rf
UTILS = error.c

PARSING = precasting.c ./parsing/check_map.c ft_substr_parsing.c \
		 ./parsing/pars_color.c ./parsing/pars_texture.c ./parsing/parsing.c \
		 ./parsing/pars_color_utils.c ./parsing/pars_texture_utils.c ./parsing/check_map_utils.c \
		 parsing/utils_prs.c

RAYCASTING = raycaster.c raycaster_utils.c mlx_hooks.c directions.c

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
