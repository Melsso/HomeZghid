/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:39:16 by smallem           #+#    #+#             */
/*   Updated: 2023/04/05 16:57:49 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)ft_calloc(i + 2, 1);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] && str[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*ft_get_buffer(char *str)
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	j = 0;
	buffer = ft_calloc(ft_strlen(str) - i + 1, 1);
	while (str && str[i])
		buffer[j++] = str[++i];
	buffer[j] = 0;
	free(str);
	str = NULL;
	return (buffer);
}

char	*free_all(char *str, char *buffer)
{
	free(buffer);
	buffer = NULL;
	free(str);
	str = NULL;
	return (NULL);
}

char	*ft_read(char *str, int fd, ssize_t bytes_read)
{
	char	*buffer;
	char	*tmp;

	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_all(str, buffer));
		buffer[bytes_read] = 0;
		tmp = str;
		str = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(str, '\n'))
			break ;
	}
	free(buffer);
	buffer = NULL;
	if (bytes_read == 0 && str[0] == 0)
	{
		free(str);
		str = NULL;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*tmp;
	char		*line;
	ssize_t		bytes_read;

	if (!str)
		str = ft_calloc(1, 1);
	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	str = ft_read(str, fd, bytes_read);
	if (str == NULL)
		return (NULL);
	line = ft_get_line(str);
	tmp = str;
	str = ft_get_buffer(tmp);
	return (line);
}
