/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_small_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:06:00 by tridley           #+#    #+#             */
/*   Updated: 2025/04/24 16:40:20 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

int	is_escapable_in_dquote(char c)
{
	return (c == '"' || c == '\\' || c == '$' || c == '`');
}

int	get_operator_length(const char *str)
{
	if ((str[0] == '>' || str[0] == '<') && str[1] == str[0])
		return (2);
	return (1);
}

int	in_quotes(const char *input, int pos)
{
	t_lex_state	state;
	int			i;

	state = STATE_NORMAL;
	i = 0;
	while (i < pos)
	{
		state = get_lexer_state(state, input[i], input[i + 1]);
		i++;
	}
	return (state == STATE_SINGLE_QUOTE || state == STATE_DOUBLE_QUOTE);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\v'
		|| c == '\r');
}
