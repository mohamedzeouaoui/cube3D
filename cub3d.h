#ifndef CUBD3D_H
#define CUB3D_H

# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <X11/X.h>
# include <SDL2/SDL.h>
# include "minilibx-linux/mlx.h"

#define ANSI_COLOR_RESET "\033[0m"
#define ANSI_COLOR_BLACK "\033[30m"
#define ANSI_COLOR_RED "\033[31m"
#define ANSI_COLOR_GREEN "\033[32m"
#define ANSI_COLOR_YELLOW "\033[33m"
#define ANSI_COLOR_BLUE "\033[34m"
#define ANSI_COLOR_MAGENTA "\033[35m"
#define ANSI_COLOR_CYAN "\033[36m"
#define ANSI_COLOR_WHITE "\033[37m"

#define WIDTH 1280
#define HEIGHT 720
#define MINI_MAP_H 60
#define MINI_MAP_W 100
#define BLOCK_SIZE 64
#define BLOCK_SIZE_2D 64
#define MINI_MAP_X 100
#define MINI_MAP_Y 100
#define PI 3.141592653589793
#define FOV 60
#define FOV_RAD (FOV * (PI / 180))
// view height
#define CUB3D_USAGE "usage ./cub3d [/path/to/map.cub]!"
#define ERR_INVALID_FILENAME "The map file must be ending with .cub!"
#define ERR_NO_PLAYER "No player found!"

typedef struct s_player
{
    int x;
    int y;
    int x_pixel;
    int y_pixel;
    double pva; //player view angle
    double rotaion_speed;
    int radius;
    int move_speed;
    int direction;
}   t_player;

typedef struct s_image
{
    void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}   t_img;

typedef struct s_texture
{
    int vert;
    int hor;
    int wall_cord;
    char *path;
    void	*img;
    char *tex_data;
    int width;
    int height;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}   t_tex;

typedef struct s_window
{
    void *cnx;
    void *win;
    t_img img;
}   t_window;

typedef struct s_ray
{
    double x;
    double y;
    double dst;
    double ray_angle;
}   t_ray;

typedef struct s_keys
{
    int forward;
    int backward;
    int left;
    int right;
}   t_keys;

typedef struct s_menu
{
    int index;
    int started;
    int entred;
    int ended;
    t_tex menu_img;
}   t_menu;

typedef struct s_game
{
    char *filename;
    int   map_len;
    int   map_width;
    char    **map;
    void *img;
    double view_height;
    double wall_hit_x;
    double wall_hit_y;
    t_player player;
    t_window window;
    t_ray ver_ray;
    t_ray hor_ray;
    t_keys keys;
    t_tex wall;
    t_tex door;
    t_tex p0;
    t_tex p1;
    t_tex p2;
    t_tex p3;
    t_tex p4;
    t_menu menu;
}   t_game;

// parse
char **parse_map(const char *file_name, t_game *game);
void find_player(t_game *game);



void ft_mlx(t_game *game);
void	ft_mlx_pixel_put(t_game *game, int x, int y, int color);

void    setup(t_game *game, int ac, char **av);
void	ft_panic(const char *msg);
int     ft_error(const char *msg);
void draw_map(t_game *game);
int found_wall(t_game *game, int x_pos, int y_pos);
double normalize_angle(double angle);
int found_door(t_game *game, int x_pos, int y_pos);
int doors(int keycode, t_game *game);

//hooks
int keys(int keycode, void *game1);
int doors(int keycode, t_game *game);
int mouse_move_hook(int x, int y, void *game1);
int drawer(t_game *game);
int ft_close(t_window *window);

//
void draw_menu(t_game *game);

// raycast_utils
int facing_north(t_game *game);
int facing_south(t_game *game);
int facing_west(t_game *game);
int facing_east(t_game *game);

//mini map
void draw_mini_map(t_game *game);

//raycaster
void cast_rays(t_game *game);

//ray utils
double count_distance(double x1, double x2, double y1, double y2);

#endif