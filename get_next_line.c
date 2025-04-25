/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:09 by danielji          #+#    #+#             */
/*   Updated: 2025/04/25 18:50:32 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "get_next_line.h"

char	*file_to_buffer(int fd)
{
	char	*buffer;
	ssize_t	bytes_read;

	bytes_read = 0;
	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	return (buffer);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*buffer;
	char	*stash;
	int		i;

	i = 0;
	buffer = file_to_buffer(fd);
	while (buffer[i])
	{
		if (buffer[i++] == '\n')
			break;
		i++;
	}
	line = ft_strdup("");
	line = ft_strjoin(line, ft_substr(buffer, 0, i));
	free(buffer);
	return (line);
}

int main(void)
{
	int		i;
	int		fd;
	char	*line;
	
	i = 0;
	fd = open("./pinker_language.txt", O_RDONLY);
	printf("[START]\n");
	line = get_next_line(fd);
	printf("%s", line);
	printf("\n[END]\n");
	
	close(fd);
}
