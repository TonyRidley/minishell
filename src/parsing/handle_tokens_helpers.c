/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:47:51 by tridley           #+#    #+#             */
/*   Updated: 2025/07/09 14:19:37 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "error_ids.h"
#include "libft.h"
#include "parsing.h"

static int	has_quotes(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	handle_open_error(char *filename, t_cmd *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_exit_status = 2;
	command->redir_failed = 1;
	command->failed_redir = ft_strdup(filename);
	return (-1);
}

int	validate_redirection(t_token *tok, char *filename, t_cmd *command)
{
	if (command->redir_failed)
		return (-1);
	if (tok->type == TOKEN_REDIRECT_IN)
		return (handle_redirect_in(filename, command));
	else if (tok->type == TOKEN_REDIRECT_OUT || tok->type == TOKEN_APPEND)
		return (handle_redirect_out(tok->type, filename, command));
	return (0);
}

static int	handle_heredoc_processing(t_cmd *command, t_token **token,
									char **env, int was_quoted)
{
	char	*expanded;
	int		ret;

	expanded = expand_env_vars((*token)->next->value, env);
	if (!expanded)
		return (ERR_MALLOC);
	ret = set_redirect_field(command, TOKEN_HEREDOC, expanded);
	free(expanded);
	if (ret != 0)
		return (ret);
	if (command->heredoc_count > 0)
		command->heredoc_quoted[command->heredoc_count - 1] = was_quoted;
	*token = (*token)->next;
	if (ret < 0)
		return (1);
	return (0);
}

int	cmd_datafill(t_cmd *command, t_token **token, int token_type,
						char **env)
{
	char	*expanded;
	int		ret;
	int		was_quoted;

	if (!(*token)->next || !(*token)->next->value)
		return (ERR_NULL);
	was_quoted = has_quotes((*token)->next->value);
	expanded = expand_env_vars((*token)->next->value, env);
	if (!expanded)
		return (ERR_MALLOC);
	ret = validate_redirection(*token, expanded, command);
	free(expanded);
	if (token_type == TOKEN_HEREDOC)
		return (handle_heredoc_processing(command, token, env, was_quoted));
	ret = set_redirect_field(command, token_type, (*token)->next->value);
	if (ret != 0)
		return (ret);
	*token = (*token)->next;
	if (ret < 0)
		return (1);
	return (0);
}
