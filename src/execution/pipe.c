/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:16:48 by tridley           #+#    #+#             */
/*   Updated: 2025/08/06 14:14:00 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "execution.h"
#include <sys/wait.h>
#include "parsing.h"

static int	setup_pipes(int pipe_fd[2]);
static int	handle_child_process(t_cmd *current, char **env,
				int prev_pipe_read, int pipe_fd[2]);
static int	handle_parent_process(int *prev_pipe_read, int pipe_fd[2],
				t_cmd **current);

int	execute_pipeline_child(t_pipeline *pl)
{
	pid_t	pid;

	if (pl->current->next && setup_pipes(pl->pipe_fd) != 0)
		return (g_exit_status);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), g_exit_status = 1, g_exit_status);
	else if (pid == 0)
	{
		setup_child_signals();
		exit(handle_child_process(pl->current, pl->env,
				pl->prev_pipe_read, pl->pipe_fd));
	}
	else
	{
		pl->last_pid = pid;
		handle_parent_process(&pl->prev_pipe_read, pl->pipe_fd, &pl->current);
	}
	return (0);
}

int	wait_for_children(pid_t last_pid)
{
	int		status;
	pid_t	pid;
	int		broken_pipe;

	broken_pipe = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGPIPE)
			broken_pipe = 1;
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else
				g_exit_status = 128 + WTERMSIG(status);
		}
		pid = wait(&status);
	}
	if (broken_pipe && g_exit_status == 0)
		ft_putstr_fd(" Broken pipe\n", 2);
	return (g_exit_status);
}

static int	setup_pipes(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

static int	handle_child_process(t_cmd *current, char **env,
				int prev_pipe_read, int pipe_fd[2])
{
	if (prev_pipe_read != -1)
	{
		dup2(prev_pipe_read, STDIN_FILENO);
		close(prev_pipe_read);
	}
	if (current->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	return (execute_command(current, &env));
}

static int	handle_parent_process(int *prev_pipe_read, int pipe_fd[2],
				t_cmd **current)
{
	if (*prev_pipe_read != -1)
		close(*prev_pipe_read);
	if ((*current)->next)
	{
		close(pipe_fd[1]);
		*prev_pipe_read = pipe_fd[0];
	}
	*current = (*current)->next;
	return (0);
}
