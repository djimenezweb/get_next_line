/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:09 by danielji          #+#    #+#             */
/*   Updated: 2025/04/25 15:27:50 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	// char	*substring;
	char	*line;
	char	*buffer;
	// int		i;
	ssize_t	bytes_read;

	bytes_read = 0;
	buffer = malloc(BUFFER_SIZE - 1);
	if (!buffer)
		return (NULL);
	
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0)
	{
		line = ft_strjoin(line, buffer);
	}

	/* 	bytes_read = read(fd, buffer, BUFFER_SIZE - 1);

	buffer[bytes_read] = '\0';
	line = ft_strdup(buffer);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE - 1);

		buffer[bytes_read] = '\0';
		line = ft_strjoin(line, buffer);
	} */
	free(buffer);
	return (line);
}

int main(void)
{
	int		fd;
	char	*line;

	fd = open("./pinker_language.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("--START--\n");
	printf("%s\n", line);
	printf("--END--\n");
	close(fd);
}
