/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:21:07 by tridley           #+#    #+#             */
/*   Updated: 2025/05/29 17:21:11 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "libft.h"
#include <stdlib.h>

static void	skip_whitespaces(char *input, int *i, int *in_filename)
{
	while (input[*i] && is_whitespace(input[*i]))
	{
		(*i)++;
		*in_filename = 0;
	}
}

static int	process_operator(t_tokenizer *data, char *input)
{
	if (!handle_special_token(data->tokens, data->current, input, data->i))
		return (0);
	if (*(data->current) && ((*data->current)->type >= TOKEN_REDIRECT_IN
			&& (*data->current)->type <= TOKEN_HEREDOC))
		return (2);
	return (1);
}

static int	process_next_token(t_tokenizer *data, char *input)
{
	int	result;

	if (*(data->in_filename))
	{
		result = 1;
		if (!handle_word_token(data->tokens, data->current, input, data->i))
			result = 0;
		*(data->in_filename) = 0;
	}
	else if (is_operator(input[*(data->i)]))
	{
		result = process_operator(data, input);
		if (result == 2)
			*(data->in_filename) = 1;
	}
	else
	{
		if (!handle_word_token(data->tokens, data->current, input, data->i))
			return (0);
		result = 1;
	}
	return (result);
}

static void	init_tokenizer(t_tokenizer *data, t_token **tokens,
						t_token **current, int *i)
{
	*tokens = NULL;
	*current = NULL;
	*i = 0;
	data->tokens = tokens;
	data->current = current;
	data->i = i;
}

t_token	*tokenize_input(char *input)
{
	t_token		*tokens;
	t_token		*current;
	int			i;
	int			in_filename;
	t_tokenizer	data;

	in_filename = 0;
	data.in_filename = &in_filename;
	init_tokenizer(&data, &tokens, &current, &i);
	while (input[i] != '\0')
	{
		skip_whitespaces(input, &i, &in_filename);
		if (input[i] == '\0')
			break ;
		if (process_next_token(&data, input) == 0)
			return (NULL);
	}
	if (!validate_token_syntax(tokens))
		return (free_tokens(tokens), NULL);
	return (tokens);
}
