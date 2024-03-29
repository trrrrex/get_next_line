/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aavramen <aavramen@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:52:10 by aavramen          #+#    #+#             */
/*   Updated: 2024/02/03 17:55:51 by aavramen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_new(char *storage)
{
	char	*new;
	int		i;

	i = 0;
	if (!storage)
		return (0);
	while (storage[i] != '\n' && storage[i] != '\0')
		i++;
	i++;
	new = ft_substr(storage, i, ft_strlen(storage));
	free(storage);
	return (new);
}

char	*ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

char	*ft_read(int fd, char *storage)
{
	int		num_bytes;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free(&storage));
	buffer[0] = '\0';
	num_bytes = 1;
	while (num_bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		num_bytes = read(fd, buffer, BUFFER_SIZE);
		if (num_bytes == -1)
		{
			free(buffer);
			return (ft_free(&storage));
		}
		if (num_bytes > 0)
		{
			buffer[num_bytes] = '\0';
			storage = ft_strjoin(storage, buffer);
		}
	}
	free(buffer);
	return (storage);
}

char	*ft_line(char	*storage)
{
	char	*line;
	int		i;

	i = 0;
	if (!storage)
		return (NULL);
	while (storage[i] != '\n' && storage[i] != '\0')
		i++;
	i++;
	line = ft_substr(storage, 0, i);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	if (!line)
	{
		return (ft_free(&buffer));
	}
	buffer = ft_new(buffer);
	return (line);
}
