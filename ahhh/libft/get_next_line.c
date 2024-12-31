/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:13:41 by ylahssin          #+#    #+#             */
/*   Updated: 2024/12/29 16:50:28 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(char **store)
{
	free(*store);
	*store = NULL;
	return (*store);
}


static int	ft_read_from_file(int fd, char *buffer, char **store)
{
	int		read_byte;
	char	*tmp;

	read_byte = read(fd, buffer, BUFFER_SIZE);
	if (read_byte <= 0)
		return (read_byte);
	buffer[read_byte] = '\0';
	tmp = ft_strjoin(*store, buffer);
	if (!tmp)
		return (-1);
	ft_free(store);
	return (*store = tmp, read_byte);
}

static char	*ft_extract_line(char **store)
{
	char	*new_pos;
	char	*tmp;
	char	*line;

	if (!*store || !**store)
		return (NULL);
	new_pos = ft_strchr(*store, '\n');
	if (new_pos)
	{
		line = ft_substr(*store, 0, new_pos - *store + 1);
		if (!line)
			return (NULL);
		tmp = ft_strdup(*store + (new_pos - *store + 1));
		if (!tmp)
			return (ft_free(&line));
		return (ft_free(store), *store = tmp, line);
	}
	if (*store || **store)
		return (line = ft_strdup(*store), ft_free(store), line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		*store;
	char			*buffer;
	char			*line;
	int				bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (ft_free(&store));
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (ft_free(&store));
	while (!ft_strchr(store, '\n'))
	{
		bytes_read = ft_read_from_file(fd, buffer, &store);
		if (bytes_read == -1)
			return (free(buffer), ft_free(&store));
		else if (bytes_read == 0)
			break ;
	}
	free(buffer);
	line = ft_extract_line(&store);
	if (!line || !*line)
		return (ft_free(&store));
	return (line);
}
