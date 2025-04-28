/* 

Compile:
cc -Wall -Werror -Wextra -D BUFFER_SIZE=512 main.c get_next_line.c get_next_line_utils.c

Valgrind tests:
cc -g -Wall -Werror -Wextra -D BUFFER_SIZE=512 main.c get_next_line.c get_next_line_utils.c -o gnl_test

valgrind --leak-check=full --track-origins=yes ./gnl_test

valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./gnl_test

*/

#include "get_next_line.h"

char *get_next_line(int fd);

int main(void)
{
	int		fd;
	char	*line;

	fd = open("test3", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
