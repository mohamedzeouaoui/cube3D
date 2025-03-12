
CC = cc
CFLAGS = #-fsanitize=address #-Werror -Wextra -Wall
RM = rm -rf
UTILS = error.c

PARSING = $(addprefix parsing/, check_map.c ft_substr_parsing.c pars_color.c pars_texture.c parsing.c pars_color_utils.c pars_texture_utils.c check_map_utils.c utils_prs.c)

RAYCASTING = gc_strdup.c gc.c $(addprefix raycasting/, mini_map.c mouse_hooks.c precasting.c raycaster.c raycaster_utils.c mlx_hooks.c directions.c draw_textures.c)

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
