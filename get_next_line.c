/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:09 by danielji          #+#    #+#             */
/*   Updated: 2025/04/25 17:37:35 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*substring;
	char	*line;
	char	*buffer;
	int		i;
	ssize_t	bytes_read;

	i = 0;
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
	while (buffer[i] && buffer[i] != '\n')
	{
		i++;
	}
	substring = ft_substr(buffer, 0, i);
	line = ft_strdup("");
	line = ft_strjoin(line, substring);
	free(substring);
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
	printf("[START--\n");
	while (i < 5)
	{
		line = get_next_line(fd);
		printf("%s", line);
		i++;
	}
	printf("\n--END]\n");
	
	close(fd);
}

