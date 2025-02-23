
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;

	if (!nmemb || !size)
	{
		nmemb = 1;
		size = 1;
	}
	buffer = malloc(nmemb * size);
	if (buffer)
		ft_bzero(buffer, nmemb * size);
	return (buffer);
}
