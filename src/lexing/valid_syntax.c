/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:47:05 by tridley           #+#    #+#             */
/*   Updated: 2025/06/11 15:47:07 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexing.h"

static int	check_consecutive_pipes(t_token *current, t_token *next)
{
	if (current->type == TOKEN_PIPE && next && next->type == TOKEN_PIPE)
	{
		print_syntax_error("||");
		return (0);
	}
	return (1);
}

static char	*get_redir_token_str(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return ("|");
	else if (type == TOKEN_REDIRECT_IN)
		return ("<");
	else if (type == TOKEN_REDIRECT_OUT)
		return (">");
	else if (type == TOKEN_APPEND)
		return (">>");
	else if (type == TOKEN_HEREDOC)
		return ("<<");
	return ("");
}

static int	check_redirection(t_token *current, t_token *next)
{
	if ((current->type >= TOKEN_REDIRECT_IN && current->type <= TOKEN_HEREDOC))
	{
		if (!next)
		{
			print_syntax_error("newline");
			return (0);
		}
		else if (next->type != TOKEN_WORD)
		{
			print_syntax_error(get_redir_token_str(next->type));
			return (0);
		}
	}
	return (1);
}

static int	check_last_token(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current && current->next)
		current = current->next;
	if (current && current->type == TOKEN_PIPE)
	{
		print_syntax_error("newline");
		return (0);
	}
	return (1);
}

int	validate_token_syntax(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	if (!check_first_token(tokens))
		return (0);
	current = tokens;
	while (current)
	{
		next = current->next;
		if (!check_consecutive_pipes(current, next))
			return (0);
		if (!check_redirection(current, next))
			return (0);
		current = next;
	}
	if (!check_last_token(tokens))
		return (0);
	return (1);
}
