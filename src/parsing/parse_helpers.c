/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:26:21 by tridley           #+#    #+#             */
/*   Updated: 2025/06/12 19:44:49 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "parsing.h"

static int	process_token_type(t_token *tmp, int *count);

static void	free_cmd_redirects(t_cmd *command)
{
	int	i;

	if (command->redirect_in)
		free(command->redirect_in);
	if (command->redirect_out)
		free(command->redirect_out);
	if (command->append)
		free(command->append);
	if (command->heredocs)
	{
		i = 0;
		while (i < command->heredoc_count)
		{
			free(command->heredocs[i]);
			i++;
		}
		free(command->heredocs);
	}
	if (command->heredoc_quoted)
		free(command->heredoc_quoted);
	if (command->failed_redir)
		free(command->failed_redir);
}

void	free_cmd(t_cmd *command)
{
	t_cmd	*next;
	int		i;

	while (command)
	{
		next = command->next;
		if (command->args)
		{
			i = 0;
			while (command->args[i])
			{
				free(command->args[i]);
				i++;
			}
			free(command->args);
		}
		free_cmd_redirects(command);
		free(command);
		command = next;
	}
}

int	count_args(t_token *token)
{
	int		count;
	t_token	*tmp;
	int		result;

	tmp = token;
	count = 0;
	while (tmp)
	{
		result = process_token_type(tmp, &count);
		if (result == 1)
			break ;
		else if (result == 2)
		{
			tmp = tmp->next;
			tmp = tmp->next;
			continue ;
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (count);
}

static int	process_token_type(t_token *tmp, int *count)
{
	if (tmp->type == TOKEN_WORD)
	{
		(*count)++;
		return (0);
	}
	else if (tmp->type == TOKEN_PIPE)
		return (1);
	else if (tmp->type >= TOKEN_REDIRECT_IN && tmp->type <= TOKEN_HEREDOC)
	{
		if (tmp->next)
			return (2);
	}
	return (0);
}
