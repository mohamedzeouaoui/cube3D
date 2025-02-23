
#include "libft.h"

static int	compute_len(int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_putnbr_fd(int n, int fd)
{
	int	sign;

	sign = 0;
	if (n == INT_MIN)
		return (ft_putstr_fd("-2147483648", fd));
	else if (n == 0)
		return (ft_putchar_fd('0', fd));
	else
	{
		if (n < 0)
		{
			sign = ft_putchar_fd('-', fd);
			n = -n;
		}
		if (n < 10)
		{
			ft_putchar_fd((n + 48), fd);
		}
		else
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putchar_fd((n % 10) + 48, fd);
		}
	}
	return (compute_len(n) + sign);
}
