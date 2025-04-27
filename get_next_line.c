/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:09 by danielji          #+#    #+#             */
/*   Updated: 2025/04/27 22:20:41 by danielji         ###   ########.fr       */
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
	if (!line)
		return (NULL);
	if (excess)
	{
		free(*excess);
		if (stack[i])
			*excess = ft_substr(stack, i, ft_strlen(stack) - i);
		else
			*excess = NULL;
	}
/* 	if (excess)
		free(*excess);
	*excess = ft_substr(stack, i, (ft_strlen(stack) - i)); */
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
	static char	*excess;
	char		*stack;
	char		*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (excess)
	{
		stack = ft_strdup(excess);
		free(excess);
	}
	else
		stack = ft_strdup("");
	if (!stack)
	{
		free(buffer);
		return (NULL);
	}
	stack = read_to_stack(fd, buffer, stack);
	free(buffer);
	if (!stack)
		return (NULL);
	line = stack_to_line(stack, &excess);
	free(stack);
	if (!line)
	{
		if (excess)
		{
			free(excess);
			excess = NULL;
		}
		return (NULL);
	}
	return (line);
}
