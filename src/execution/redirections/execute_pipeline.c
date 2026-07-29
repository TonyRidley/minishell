/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:27:36 by mschuurm          #+#    #+#             */
/*   Updated: 2025/08/06 14:31:11 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"
#include "libft.h"

static int	process_all_heredocs_first(t_cmd *cmd, char **env);
static int	pipeline_loop_and_cleanup(t_pipeline *pl);

static int	process_all_heredocs_first(t_cmd *cmd, char **env)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (current->heredoc_count > 0)
		{
			if (setup_heredoc(current, env))
				return (1);
		}
		current = current->next;
	}
	return (0);
}

static int	pipeline_loop_and_cleanup(t_pipeline *pl)
{
	int	result;

	while (pl->current)
	{
		if (execute_pipeline_child(pl) != 0)
		{
			if (pl->prev_pipe_read != -1)
				close(pl->prev_pipe_read);
			setup_signals();
			return (g_exit_status);
		}
	}
	if (pl->prev_pipe_read != -1)
		close (pl->prev_pipe_read);
	result = wait_for_children(pl->last_pid);
	setup_signals();
	if (result > 127)
		write(STDOUT_FILENO, "\n", 1);
	return (result);
}

int	execute_pipeline(t_cmd *cmd, char ***env_ptr)
{
	t_pipeline	pl;

	if (!env_ptr || !*env_ptr)
		return (1);
	if (process_all_heredocs_first(cmd, *env_ptr))
		return (g_exit_status);
	disable_signal_handling();
	pl.env = *env_ptr;
	pl.prev_pipe_read = -1;
	pl.current = cmd;
	pl.last_pid = -1;
	return (pipeline_loop_and_cleanup(&pl));
}
