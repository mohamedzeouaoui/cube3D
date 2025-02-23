
#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	count;

	count = 0;
	if (s)
	{
		count = ft_putstr_fd(s, fd);
		count += ft_putchar_fd('\n', fd);
	}
	return (count);
}
