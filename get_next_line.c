/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:09 by danielji          #+#    #+#             */
/*   Updated: 2025/04/27 21:32:43 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "get_next_line.h"

static char	*stack_to_line(char *stack, char **excess)
{
	int		i;
	char	*line;

	if (!stack || !stack[0])
		return (NULL);
	i = 0;
	while (stack[i] && stack[i] != '\n')
		i++;
	if (stack[i] == '\n')
		i++;
	line = ft_substr(stack, 0, i);
	if (excess != NULL)
		free(*excess);
	*excess = ft_substr(stack, i, ft_strlen(stack));
	return (line);
}

static char	*read_to_stack(int fd, char *buffer, char *stack)
{
	ssize_t	read_bytes;

	while (!ft_strchr(stack, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes >= 0)
			buffer[read_bytes] = '\0';
		if (read_bytes <= 0)
			break ;
		stack = ft_strjoin(stack, buffer);
		if (!stack)
			return (NULL);
	}
	return (stack);
}

char	*get_next_line(int fd)
{
	char		*stack;
	static char	*excess;
	char		*buffer;
	char		*line;

	if (BUFFER_SIZE <=0 || fd < 0)
		return (NULL);
	if (excess)
		stack = ft_strdup(excess);
	else
		stack = ft_strdup("");
	if (!stack)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	stack = read_to_stack(fd, buffer, stack);
	line = stack_to_line(stack, &excess);
	if (!line)
		return (NULL);
	free(stack);
	free(buffer);
	return (line);
}
// cc -Wall -Werror -Wextra -D BUFFER_SIZE=512 get_next_line.c get_next_line_utils.c
int main(void)
{
	int		fd;
	char	*line;
	
	fd = open("./many_end_lines", O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening the file\n");
		return (1);
	}
	
	printf("[START] buffer size=%d\n", BUFFER_SIZE);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("[END]\n");	
	close(fd);
	return (0);
}
