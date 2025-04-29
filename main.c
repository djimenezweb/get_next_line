/* THIS FILE IS FOR TESTING PURPOSES ONLY

Compile:
	cc -Wall -Werror -Wextra -D BUFFER_SIZE=512 main.c get_next_line.c get_next_line_utils.c

Valgrind tests:
	cc -g -Wall -Werror -Wextra -D BUFFER_SIZE=512 main.c get_next_line.c get_next_line_utils.c -o gnl_test

	valgrind --leak-check=full --track-origins=yes ./gnl_test

	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./gnl_test
*/

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd);

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test2", O_RDONLY);
	//fd = 0;
	if (fd < 0)
		printf("Error reading the file\n");
	printf("~ ~ ~ GET NEXT LINE ~ BUFFER SIZE: %i BYTES  ~ ~ ~\n", BUFFER_SIZE);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	if (fd > 0)
		close(fd);
	printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
	return (0);
}
