
#include "libft.h"

static ssize_t	read_from_buffer(int fd, char **history)
{
	ssize_t	bytes;
	char	*buffer;
	char	*temp;

	buffer = malloc(BUFFER_SIZE + 1);
	ft_memset(buffer, 0, BUFFER_SIZE + 1);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes <= 0)
	{
		free(buffer);
		return (bytes);
	}
	temp = *history;
	*history = ft_strjoin(*history, buffer);
	free(temp);
	free(buffer);
	return (bytes);
}

static void	cleanup_history(char **history)
{
	char	*nl;
	char	*temp;

	nl = ft_strchr(*history, '\n');
	temp = *history;
	*history = ft_strdup(nl + 1);
	free(temp);
}

static char	*get_result(char **history)
{
	char	*nl;
	char	*result;
	ssize_t	i;

	nl = ft_strchr(*history, '\n');
	if (!nl)
	{
		result = ft_strdup(*history);
		free(*history);
		*history = NULL;
		return (result);
	}
	result = malloc(nl - *history + 2);
	if (!result)
		return (NULL);
	i = 0;
	while (i < nl - *history + 1)
	{
		result[i] = (*history)[i];
		i++;
	}
	result[i] = '\0';
	cleanup_history(history);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*history;
	ssize_t		bytes;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (history == NULL)
		history = ft_strdup("");
	bytes = 1;
	while (bytes > 0 && !!history && !ft_strchr(history, '\n'))
		bytes = read_from_buffer(fd, &history);
	if (bytes < 0 || ft_strlen(history) == 0)
	{
		free(history);
		history = NULL;
		return (NULL);
	}
	return (get_result(&history));
}
