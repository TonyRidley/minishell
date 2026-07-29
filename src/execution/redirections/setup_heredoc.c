/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:57:21 by mschuurm          #+#    #+#             */
/*   Updated: 2025/06/12 19:42:06 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "parsing.h"
#include "libft.h"
#include "execution.h"

int	process_heredocs(t_cmd *command, char **env, int pipe_fd)
{
	int	i;
	int	interrupted;

	i = 0;
	interrupted = 0;
	while (i < command->heredoc_count - 1)
	{
		if (heredoc_read_loop_discard(command->heredocs[i]))
		{
			interrupted = 1;
			break ;
		}
		i++;
	}
	if (command->heredoc_count > 0 && !interrupted)
	{
		if (heredoc_read_loop(command->heredocs[command->heredoc_count - 1],
				command->heredoc_quoted[command->heredoc_count - 1],
				pipe_fd, env))
		{
			interrupted = 1;
		}
	}
	return (interrupted);
}

int	setup_heredoc(t_cmd *command, char **env)
{
	int	pipe_fd[2];
	int	t_fd;
	int	saved_stdin;
	int	interrupted;

	setup_heredoc_signals();
	if (setup_heredoc_pipes(pipe_fd, &t_fd, &saved_stdin))
	{
		setup_signals();
		return (1);
	}
	interrupted = process_heredocs(command, env, pipe_fd[1]);
	setup_signals();
	if (finalize_heredoc(pipe_fd, t_fd, saved_stdin, interrupted))
	{
		if (interrupted)
			g_exit_status = 130;
		return (1);
	}
	return (0);
}

void	restore_redirections(int original_stdin, int original_stdout)
{
	if (original_stdin != -1)
	{
		if (dup2(original_stdin, STDIN_FILENO) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
		}
		close(original_stdin);
	}
	if (original_stdout != -1)
	{
		if (dup2(original_stdout, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
		}
		close(original_stdout);
	}
}
