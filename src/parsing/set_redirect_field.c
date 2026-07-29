/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect_field.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:35:47 by tridley           #+#    #+#             */
/*   Updated: 2025/06/12 19:35:49 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "parsing.h"

static char	*duplicate_value(char *value)
{
	char	*dup_value;

	dup_value = ft_strdup(value);
	if (!dup_value)
		return (NULL);
	return (dup_value);
}

static int	handle_redirect_in_out_field(t_cmd *command, char *value,
	int token_type)
{
	char	*dup_value;

	dup_value = duplicate_value(value);
	if (!dup_value)
		return (ERR_MALLOC);
	if (token_type == TOKEN_REDIRECT_IN)
	{
		if (command->redirect_in)
			free(command->redirect_in);
		command->redirect_in = dup_value;
	}
	if (token_type == TOKEN_REDIRECT_OUT)
	{
		if (command->redirect_out)
			free(command->redirect_out);
		command->redirect_out = dup_value;
	}
	return (0);
}

static int	handle_append_field(t_cmd *command, char *value)
{
	char	*dup_value;

	dup_value = duplicate_value(value);
	if (!dup_value)
		return (ERR_MALLOC);
	if (command->append)
		free(command->append);
	command->append = dup_value;
	return (0);
}

static int	handle_heredoc_field(t_cmd *command, char *value)
{
	char	*dup_value;
	size_t	old_size;

	dup_value = duplicate_value(value);
	if (!dup_value)
		return (ERR_MALLOC);
	old_size = command->heredoc_count * sizeof(char *);
	command->heredocs = ft_realloc(command->heredocs,
			old_size, sizeof(char *) * (command->heredoc_count + 1));
	old_size = command->heredoc_count * sizeof(int);
	command->heredoc_quoted = ft_realloc(command->heredoc_quoted,
			old_size, sizeof(int) * (command->heredoc_count + 1));
	if (!command->heredocs || !command->heredoc_quoted)
	{
		free(dup_value);
		return (ERR_MALLOC);
	}
	command->heredocs[command->heredoc_count] = dup_value;
	command->heredoc_quoted[command->heredoc_count] = 0;
	command->heredoc_count++;
	return (0);
}

int	set_redirect_field(t_cmd *command, int token_type, char *value)
{
	if (token_type == TOKEN_REDIRECT_IN || token_type == TOKEN_REDIRECT_OUT)
		return (handle_redirect_in_out_field(command, value, token_type));
	else if (token_type == TOKEN_APPEND)
		return (handle_append_field(command, value));
	else if (token_type == TOKEN_HEREDOC)
		return (handle_heredoc_field(command, value));
	return (0);
}
