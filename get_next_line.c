/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:09 by danielji          #+#    #+#             */
/*   Updated: 2025/04/23 15:25:51 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	int		buf_size;
	int		fd;
	char	*buf;

	buf_size = 20;
	fd = open("./test_file");
	buf = malloc(buf_size * sizeof(char));
	while (buf_size > 0)
	{
		read(fd, buf, (size_t)buf_size);
		buf_size--;
	}
	free(buf);
	close(fd);
}