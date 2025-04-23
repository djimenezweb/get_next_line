/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:09 by danielji          #+#    #+#             */
/*   Updated: 2025/04/23 17:25:56 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int BUFFER_SIZE;

static int BUFFER_SIZE = 20;

char	*get_next_line(int fd)
{
	char	*buf;
	int		i;

	i = 0;
	buf = malloc(BUFFER_SIZE * sizeof(char));
	read(fd, buf, BUFFER_SIZE);
	return (buf);
}

int main(void)
{
	int		fd;
	char	*str;

	fd = open("./test_file", O_RDONLY);
	while (str)
	{
		str = get_next_line(fd);
		printf("%s", str);
	}
	close(fd);
}