/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:54:41 by tridley           #+#    #+#             */
/*   Updated: 2025/06/10 19:15:25 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing.h"
#include "libft.h"

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;
	char	quote_type;

	if (!str)
		return (ft_strdup(""));
	result = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote_type = '\0';
	while (str && str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote_type == '\0')
			quote_type = str[i];
		else if (str[i] == quote_type)
			quote_type = '\0';
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

int	get_var_name_length(char *str, int start)
{
	int	len;
	int	has_braces;

	has_braces = 0;
	len = 0;
	if (str[start + 1] == '{')
	{
		has_braces = 1;
		start++;
	}
	start++;
	if (str[start] == '?')
	{
		if (has_braces)
			return (-1);
		return (1);
	}
	while (str[start + len] && (ft_isalnum(str[start + len])
			|| str[start + len] == '_'))
		len++;
	if (has_braces && str[start + len] != '}')
		return (-1);
	if (has_braces)
		return (len + 2);
	return (len);
}

char	*extract_var_name(char *str, int start, int *var_len)
{
	int		len;
	int		has_braces;
	char	*name;

	has_braces = (str[start + 1] == '{');
	len = *var_len;
	if (str[start + 1] == '?')
	{
		if (has_braces)
			*var_len = 3;
		else
			*var_len = 1;
		return (ft_strdup("?"));
	}
	if (has_braces)
	{
		name = ft_substr(str, start + 2, len - 2);
		*var_len = len;
	}
	else
	{
		name = ft_substr(str, start + 1, len);
		*var_len = len;
	}
	return (name);
}

int	calculate_expanded_length(char *str, char **env)
{
	t_expand_state	state;

	if (!str)
		return (0);
	ft_memset(&state, 0, sizeof(t_expand_state));
	state.envp = env;
	while (str && str[state.i])
	{
		if (str[state.i] == '\'' && (state.i == 0 || str[state.i - 1] != '\\'))
			state.in_single_quote = !state.in_single_quote;
		if (str[state.i] == '$' && !state.in_single_quote && str[state.i + 1])
			handle_variable(&state, str, NULL);
		else
		{
			state.len++;
			state.i++;
		}
	}
	if (state.len > 0)
		return (state.len);
	return (1);
}
