/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:47:01 by tridley           #+#    #+#             */
/*   Updated: 2025/05/17 14:47:24 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing.h"
#include "libft.h"
#include "minishell.h"

static int	init_command_args(t_cmd *command, t_token *token, int *arg_count);
static int	process_token(t_token **token_ptr, t_cmd **cmd_ptr, t_token_data d);
static int	process_tokens_loop(t_token **token, t_cmd **cmd, t_token_data d);

int	token_to_cmd(t_token *token, t_cmd *command, char **env)
{
	int				i;
	int				ret;
	int				arg_count;
	int				skip_next;
	t_token_data	data;

	if (!token || !command)
		return (ERR_NULL);
	ret = init_command_args(command, token, &arg_count);
	if (ret != 0)
		return (ret);
	i = 0;
	skip_next = 0;
	data.i = &i;
	data.arg_count = &arg_count;
	data.env = env;
	data.skip_next = &skip_next;
	ret = process_tokens_loop(&token, &command, data);
	if (ret != 0)
		return (ret);
	return (command->args[i] = NULL, command->args_count = i, 0);
}

static int	process_tokens_loop(t_token **token, t_cmd **cmd, t_token_data d)
{
	int		ret;
	t_token	*current;

	current = *token;
	while (current)
	{
		ret = process_token(&current, cmd, d);
		if (ret == 1)
			continue ;
		else if (ret != 0)
			return (ret);
		current = current->next;
	}
	*token = current;
	return (0);
}

static int	process_token(t_token **token_ptr, t_cmd **cmd_ptr, t_token_data d)
{
	int		ret;
	t_token	*token;

	token = *token_ptr;
	if (*d.skip_next)
		return (*d.skip_next = 0, 0);
	if (token->type == TOKEN_WORD)
		handle_parse_word_token(*cmd_ptr, token, d.i, *d.arg_count);
	else if (token->type >= TOKEN_REDIRECT_IN && token->type <= TOKEN_HEREDOC)
	{
		ret = handle_redirect_token(*cmd_ptr, token_ptr, d.env);
		if (ret != 0)
			return (ret);
		*d.skip_next = 1;
		return (1);
	}
	else if (token->type == TOKEN_PIPE)
	{
		ret = handle_pipe_token(cmd_ptr, token, d.i, d.arg_count);
		if (ret != 0)
			return (ret);
	}
	return (0);
}

static int	init_command_args(t_cmd *command, t_token *token, int *arg_count)
{
	*arg_count = count_args(token);
	command->args = ft_calloc(*arg_count + 1, sizeof(char *));
	if (!command->args)
		return (ERR_MALLOC);
	return (0);
}
