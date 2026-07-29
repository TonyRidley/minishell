/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_simple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:21:53 by mschuurm          #+#    #+#             */
/*   Updated: 2025/08/06 14:18:03 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "parsing.h"
#include "libft.h"
#include "execution.h"

static char	*resize_line_buffer(char *line, int size)
{
	char	*new_line;
	int		old_size;

	old_size = size / 2;
	new_line = ft_realloc(line, old_size, size);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	return (new_line);
}

static int	process_single_char(char **line, int *size, int *i)
{
	char	c;
	int		ret;

	ret = read(0, &c, 1);
	if (ret == 0)
	{
		write(1, "\n", 1);
		free(*line);
		return (-1);
	}
	if (ret < 0)
	{
		return (free(*line), -1);
	}
	if (c == '\n')
		return (1);
	if (*i >= *size - 1)
	{
		*size *= 2;
		*line = resize_line_buffer(*line, *size);
		if (!*line)
			return (-1);
	}
	(*line)[(*i)++] = c;
	return (0);
}

static int	setup_stdin_if_needed(void)
{
	int	tty_fd;

	tty_fd = open("/dev/tty", O_RDONLY);
	if (tty_fd != -1)
	{
		dup2(tty_fd, 0);
		close(tty_fd);
		return (1);
	}
	return (0);
}

char	*read_line_simple(void)
{
	char	*line;
	int		i;
	int		size;
	int		result;

	if (!setup_stdin_if_needed())
		return (NULL);
	size = 100;
	line = malloc(size);
	if (!line)
		return (NULL);
	write(1, "> ", 2);
	i = 0;
	while (1)
	{
		result = process_single_char(&line, &size, &i);
		if (result == -1)
			return (NULL);
		if (result == 1)
			break ;
	}
	line[i] = '\0';
	return (line);
}
