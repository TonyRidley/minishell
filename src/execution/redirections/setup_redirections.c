/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:04:16 by tridley           #+#    #+#             */
/*   Updated: 2025/07/09 15:24:43 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "parsing.h"
#include "libft.h"
#include "execution.h"

static int	setup_redirect_in(t_cmd *command, int *fd)
{
	*fd = open(command->redirect_in, O_RDONLY);
	if (*fd == -1 || dup2(*fd, STDIN_FILENO) == -1)
	{
		if (*fd != -1)
			close(*fd);
		return (1);
	}
	close(*fd);
	return (0);
}

static int	setup_redirect_out(t_cmd *command, int *fd)
{
	*fd = open(command->redirect_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1 || dup2(*fd, STDOUT_FILENO) == -1)
	{
		if (*fd != -1)
			close(*fd);
		return (1);
	}
	close(*fd);
	return (0);
}

static int	setup_redirect_append(t_cmd *command, int *fd)
{
	*fd = open(command->append, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1 || dup2(*fd, STDOUT_FILENO) == -1)
	{
		if (*fd != -1)
			close(*fd);
		return (1);
	}
	close(*fd);
	return (0);
}

static int	apply_redirections(t_cmd *command, char **env)
{
	int	fd;	

	(void)env;
	if (command->redirect_in && setup_redirect_in(command, &fd))
		return (1);
	if (command->append && setup_redirect_append(command, &fd))
		return (1);
	if (command->redirect_out && setup_redirect_out(command, &fd))
		return (1);
	return (0);
}

int	setup_redirections(t_cmd *command, int *original_stdin,
	int *original_stdout, char **env)
{
	*original_stdin = -1;
	*original_stdout = -1;
	if (command->redir_failed)
		return (1);
	if (command->redirect_in || command->redirect_out
		|| command->append || command->heredoc_count > 0)
	{
		*original_stdin = dup(STDIN_FILENO);
		*original_stdout = dup(STDOUT_FILENO);
		if (*original_stdin == -1 || *original_stdout == -1)
			return (ft_putstr_fd(strerror(errno), 2), write(2, "\n", 1), 1);
	}
	if (apply_redirections(command, env))
		return (1);
	return (0);
}
