/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:36:08 by tridley           #+#    #+#             */
/*   Updated: 2025/05/21 15:36:11 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "error_ids.h"
#include "libft.h"
#include "parsing.h"

int	handle_redirect_in(char *filename, t_cmd *command)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (handle_open_error(filename, command));
	close(fd);
	return (0);
}

int	handle_redirect_out(int type, char *filename, t_cmd *command)
{
	int	fd;
	int	flags;

	if (type == TOKEN_REDIRECT_OUT)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else
		flags = O_CREAT | O_WRONLY | O_APPEND;
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
			ft_putstr_fd(": Permission denied\n", 2);
		else
		{
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
		}
		g_exit_status = 1;
		command->redir_failed = 1;
		command->failed_redir = ft_strdup(filename);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_parse_word_token(t_cmd *command, t_token *token, int *i,
			int arg_count)
{
	if (*i < arg_count)
		command->args[(*i)++] = token->value;
	return (0);
}

int	handle_redirect_token(t_cmd *command, t_token **token, char **env)
{
	int	ret;

	ret = cmd_datafill(command, token, (*token)->type, env);
	if (ret != 0 && ret != 1)
	{
		if (ret == ERR_NULL)
			g_exit_status = ret;
		return (ret);
	}
	return (ret);
}

int	handle_pipe_token(t_cmd **command, t_token *token, int *i, int *arg_count)
{
	(*command)->args[*i] = NULL;
	(*command)->args_count = *i;
	(*command)->next = ft_calloc(1, sizeof(t_cmd));
	if (!(*command)->next)
		return (ERR_MALLOC);
	(*command)->next->previous = *command;
	*command = (*command)->next;
	if (token->next)
		*arg_count = count_args(token->next);
	else
		*arg_count = 0;
	(*command)->args = ft_calloc(*arg_count + 1, sizeof(char *));
	if (!(*command)->args)
		return (ERR_MALLOC);
	*i = 0;
	return (0);
}
