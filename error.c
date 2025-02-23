#include "cub3d.h"

void	ft_panic(const char *msg)
{
	perror(msg);
	exit(1);
}

int	ft_error(const char *msg)
{
	ft_putstr_fd(ANSI_COLOR_RED, STDERR_FILENO);
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd(ANSI_COLOR_RESET, STDERR_FILENO);
	ft_putendl_fd((char *)msg, STDERR_FILENO);
	return (1);
}
