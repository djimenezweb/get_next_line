/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:09 by danielji          #+#    #+#             */
/*   Updated: 2025/04/27 13:45:36 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "get_next_line.h"

static char	*stash_to_line(char *stash, char **excess)
{
	int		i;
	char	*line;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	i++;
	line = ft_substr(stash, 0, i);
	free(*excess);
	*excess = ft_substr(stash, i, ft_strlen(stash));
	return (line);
}

static ssize_t	read_to_buffer(int fd, char *buffer)
{
	ssize_t		read_bytes;

	read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes >= 0)
		buffer[read_bytes] = '\0';
	return (read_bytes);
}

char	*get_next_line(int fd)
{
	char		*stash;
	static char	*excess;
	char		*buffer;
	char		*line;
	ssize_t		read_bytes;

	if (!fd || fd < 0)
		return (NULL);
	if (excess)
		stash = ft_strdup(excess);
	else
		stash = ft_strdup("");
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer || !stash)
		return (NULL);
	while (!ft_strchr(stash, '\n'))
	{
		read_bytes = read_to_buffer(fd, buffer);
		if (read_bytes <= 0)
			break ;
		stash = ft_strjoin(stash, buffer);
	}
	line = stash_to_line(stash, &excess);
	if (!line)
		return (NULL);
	free(stash);
	free(buffer);
	return (line);
}

/* int main(void)
{
	int		i;
	int		fd;
	char	*line1;
	char	*line2;
	char	*line3;
	
	i = 0;
	fd = open("./test_file", O_RDONLY);
	printf("[START]\n");
	line1 = get_next_line(fd);
	printf("--> LINE: %s", line1);
	line2 = get_next_line(fd);
	printf("--> LINE: %s", line2);
	line3 = get_next_line(fd);
	printf("--> LINE: %s", line3);
	printf("[END]\n");
	
	close(fd);
}
 */