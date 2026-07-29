/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:58:26 by tridley           #+#    #+#             */
/*   Updated: 2025/05/17 17:10:41 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing.h"
#include "libft.h"
#include <stdlib.h>

char	*get_env_value(char *name, char **env)
{
	int	i;
	int	name_len;

	if (!name || !env)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			return (&env[i][name_len + 1]);
		i++;
	}
	return (NULL);
}

static int	has_quotes(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

char	*expand_env_vars(char *str, char **env)
{
	char	*result;
	char	*unquoted;
	int		len;

	if (!str)
		return (NULL);
	len = calculate_expanded_length(str, env);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	perform_expansion(str, result, env);
	if (has_quotes(result))
	{
		unquoted = remove_quotes(result);
		free(result);
		return (unquoted);
	}
	return (result);
}

void	perform_expansion(char *str, char *result, char **env)
{
	t_expand_state	state;

	ft_memset(&state, 0, sizeof(t_expand_state));
	state.envp = env;
	while (str[state.i])
	{
		if (str[state.i] == '\'' && (state.i == 0 || str[state.i - 1] != '\\'))
			state.in_single_quote = !state.in_single_quote;
		if (str[state.i] == '$' && !state.in_single_quote && str[state.i + 1])
			handle_variable(&state, str, result);
		else
			result[state.j++] = str[state.i++];
	}
	result[state.j] = '\0';
}
