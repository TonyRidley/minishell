/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_big_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:30:16 by tridley           #+#    #+#             */
/*   Updated: 2025/04/24 18:01:41 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "libft.h"
#include <stdlib.h>
#include "minishell.h"

char	*extract_word(const char *input, int *i, t_lex_state state)
{
	int			start;
	int			len;
	int			op_len;

	state = STATE_NORMAL;
	start = *i;
	len = 0;
	while (input[*i])
	{
		if (state == STATE_NORMAL && is_operator(input[*i]))
		{
			if (len == 0)
				return (op_len = get_operator_length(input + *i),
					(*i) += op_len, ft_substr(input, start, op_len));
			break ;
		}
		if (state == STATE_NORMAL && is_whitespace(input[*i]))
			break ;
		state = get_lexer_state(state, input[*i], input[*i + 1]);
		(*i)++;
		len++;
	}
	if (!validate_quotes(state))
		return (NULL);
	return (ft_substr(input, start, len));
}

t_token_type	identify_token_type(const char *str, int len)
{
	if (len == 1)
	{
		if (str[0] == '|')
			return (TOKEN_PIPE);
		else if (str[0] == '<')
			return (TOKEN_REDIRECT_IN);
		else if (str[0] == '>')
			return (TOKEN_REDIRECT_OUT);
	}
	else if (len == 2)
	{
		if (str[0] == '>' && str[1] == '>')
			return (TOKEN_APPEND);
		else if (str[0] == '<' && str[1] == '<')
			return (TOKEN_HEREDOC);
	}
	return (TOKEN_WORD);
}

t_lex_state	get_lexer_state(t_lex_state current_state, char c, char next_c)
{
	if (current_state == STATE_NORMAL)
	{
		if (c == '\'')
			return (STATE_SINGLE_QUOTE);
		else if (c == '"')
			return (STATE_DOUBLE_QUOTE);
		else if (c == '\\')
			return (STATE_ESCAPED);
	}
	else if (current_state == STATE_SINGLE_QUOTE && c == '\'')
		return (STATE_NORMAL);
	else if (current_state == STATE_DOUBLE_QUOTE)
	{
		if (c == '\\' && is_escapable_in_dquote(next_c))
			return (STATE_ESCAPED);
		else if (c == '"')
			return (STATE_NORMAL);
	}
	else if (current_state == STATE_ESCAPED)
		return (STATE_NORMAL);
	return (current_state);
}

int	add_token(t_token **tokens, t_token **current, t_token_type type,
	char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (free(value), 0);
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	if (*tokens == NULL)
	{
		*tokens = new_token;
		*current = new_token;
	}
	else
	{
		(*current)->next = new_token;
		*current = new_token;
	}
	return (1);
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}
