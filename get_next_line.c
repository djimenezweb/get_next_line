/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:09 by danielji          #+#    #+#             */
/*   Updated: 2025/04/24 11:03:46 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "get_next_line.h"

static int BUFFER_SIZE;

static int BUFFER_SIZE = 256;

char	*get_next_line(int fd)
{
	int		i;
	char	c;
	char	*buffer;
	char	*stash;
	char	*line;
	ssize_t	n_bytes;
	
	i = 0;
	buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer)
		return (NULL);
	
	while(n_bytes > 0)
	{
		n_bytes = read(fd, &c, 1);
		buffer[i] = c;
		i++;
	}
	buffer[i] = '\0';
	stash = ft_strjoin(buffer, stash);
	line = ft_strdup(buffer);
/* 	if (n_bytes < 0)
	{
		return (NULL);
	} */
	return (line);
}

int main(void)
{
	int		fd;
	char	*str;

	fd = open("./pinker_language", O_RDONLY);
	while (str)
	{
		str = get_next_line(fd);
		printf("%s", str);
	}
	close(fd);
}
