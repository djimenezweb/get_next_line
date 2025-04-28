/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:09 by danielji          #+#    #+#             */
/*   Updated: 2025/04/28 12:19:17 by danielji         ###   ########.fr       */
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
	if (!line)
		return (NULL);
	return (line);
}

static char	*read_to_stack(int fd, char *stack)
{
	ssize_t	read_bytes;
	char	*buffer;
	char	*new_stack;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	while (!ft_strchr(buffer, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes >= 0)
			buffer[read_bytes] = '\0';
		if (read_bytes <= 0)
			break ;
		new_stack = ft_strjoin(stack, buffer);
		free(stack);
		if (!new_stack)
			return (NULL);
		stack = new_stack;
	}
	free(buffer);
	return (stack);
}

char	*get_next_line(int fd)
{
	char		*stack;
	static char	*excess;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (excess)
		stack = ft_strdup(excess);
	else
		stack = ft_strdup("");
	if (!stack)
		return (NULL);
	stack = read_to_stack(fd, stack);
	line = stack_to_line(stack, &excess);
	free(stack);
	if (!line && excess)
	{
		free(excess);
		excess = NULL;
	}
	return (line);
}
