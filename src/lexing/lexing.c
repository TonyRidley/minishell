/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:06:00 by tridley           #+#    #+#             */
/*   Updated: 2025/04/11 13:11:21 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "libft.h"
#include <stdlib.h>

int	handle_special_token(t_token **tokens, t_token **current,
	const char *input, int *i)
{
	t_token_type	type;
	char			operator[2];
	int				op_len;

	operator[0] = 0;
	operator[1] = 0;
	op_len = get_operator_length(input + *i);
	ft_strlcpy(operator, input + *i, op_len + 1);
	type = identify_token_type(operator, op_len);
	if (!add_token(tokens, current, type, ft_strdup(operator)))
	{
		if (*tokens)
			free_tokens(*tokens);
		return (0);
	}
	*i += op_len;
	return (1);
}

int	handle_word_token(t_token **tokens, t_token **current,
	const char *input, int *i)
{
	char		*word;
	t_lex_state	state;

	state = STATE_NORMAL;
	word = extract_word(input, i, state);
	if (!word)
		return (0);
	if (!add_token(tokens, current, TOKEN_WORD, word))
	{
		free(word);
		if (*tokens)
			free_tokens(*tokens);
		return (0);
	}
	return (1);
}

void	print_syntax_error(char *token_str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token_str, 2);
	ft_putstr_fd("'\n", 2);
	g_exit_status = 2;
}

int	check_first_token(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (tokens->type == TOKEN_PIPE)
	{
		print_syntax_error("|");
		return (0);
	}
	return (1);
}

int	validate_quotes(t_lex_state state)
{
	if (state == STATE_SINGLE_QUOTE || state == STATE_DOUBLE_QUOTE)
	{
		ft_putstr_fd("syntax error: unterminated quoted string\n", 2);
		g_exit_status = 2;
		return (0);
	}
	return (1);
}
