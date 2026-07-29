/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:37:35 by mschuurm          #+#    #+#             */
/*   Updated: 2025/07/08 17:22:05 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "parsing.h"
#include "libft.h"
#include "execution.h"

int	setup_heredoc_pipes(int *pipe_fd, int *t_fd, int *saved_stdin)
{
	if (pipe(pipe_fd) == -1)
		return (1);
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), 1);
	*t_fd = -1;
	return (0);
}

int	heredoc_read_loop_discard(char *delimiter)
{
	char	*line;

	while (1)
	{
		line = read_line_simple();
		if (!line)
			return (1);
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		free(line);
	}
	return (0);
}

void	process_heredoc_line(char *line, int is_quoted, int pipe_fd, char **env)
{
	char	*expanded_line;

	if (is_quoted)
	{
		ft_putstr_fd(line, pipe_fd);
	}
	else
	{
		expanded_line = expand_env_vars(line, env);
		if (expanded_line)
		{
			ft_putstr_fd(expanded_line, pipe_fd);
			free(expanded_line);
		}
	}
	ft_putchar_fd('\n', pipe_fd);
}

int	heredoc_read_loop(char *delimiter, int is_quoted, int pipe_fd, char **env)
{
	char	*line;

	while (1)
	{
		line = read_line_simple();
		if (!line)
			return (1);
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		process_heredoc_line(line, is_quoted, pipe_fd, env);
		free(line);
	}
	return (0);
}

int	finalize_heredoc(int *pipe_fd, int t_fd, int saved_stdin, int ir)
{
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	if (t_fd != -1)
		close(t_fd);
	close(pipe_fd[1]);
	if (ir)
	{
		close(pipe_fd[0]);
		return (1);
	}
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		return (close(pipe_fd[0]), 1);
	close(pipe_fd[0]);
	return (0);
}
