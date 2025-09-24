/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:44:59 by marvin            #+#    #+#             */
/*   Updated: 2025/06/17 11:44:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*old_buffer;
	char		*temp;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FOPEN_MAX)
		return (NULL);
	temp = ft_strjoin_gnl(NULL, buffer[fd]);
	bytes_read = 1;
	while (!ft_strchr_gnl(temp) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(temp), NULL);
		buffer[fd][bytes_read] = '\0';
		old_buffer = temp;
		temp = ft_strjoin_gnl(temp, buffer[fd]);
		free(old_buffer);
	}
	old_buffer = ft_get_line_gnl(temp, buffer[fd]);
	if (!old_buffer)
		return (free(temp), NULL);
	return (free(temp), old_buffer);
}
