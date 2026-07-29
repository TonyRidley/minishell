/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:31:47 by tridley           #+#    #+#             */
/*   Updated: 2025/06/10 19:24:05 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static void	handle_exit_status(t_expand_state *state, char *result)
{
	char	*exit_str;

	exit_str = ft_itoa(g_exit_status);
	if (result)
	{
		ft_strlcpy(&result[state->j], exit_str, ft_strlen(exit_str) + 1);
		state->j += ft_strlen(exit_str);
	}
	else
		state->len += ft_strlen(exit_str);
	free(exit_str);
}

static void	handle_env_value(t_expand_state *state, char *var_name,
	char *result)
{
	char	*var_value;

	var_value = get_env_value(var_name, state->envp);
	if (var_value)
	{
		if (result)
		{
			ft_strlcpy(&result[state->j], var_value, ft_strlen(var_value) + 1);
			state->j += ft_strlen(var_value);
		}
		else
			state->len += ft_strlen(var_value);
	}
}

static void	extract_expand_v(t_expand_state *state, char *str, char *r, int v_l)
{
	char	*var_name;

	var_name = extract_var_name(str, state->i, &v_l);
	if (!var_name)
	{
		state->i += v_l + 1;
		return ;
	}
	if (!ft_strcmp(var_name, "?"))
		handle_exit_status(state, r);
	else
		handle_env_value(state, var_name, r);
	free(var_name);
	state->i += v_l + 1;
}

static void	handle_no_variable(t_expand_state *state, char *str, char *result)
{
	if (result)
		result[state->j++] = str[state->i++];
	else
	{
		state->len++;
		state->i++;
	}
}

void	handle_variable(t_expand_state *state, char *str, char *result)
{
	int	var_len;

	if (!str || !str[state->i + 1])
	{
		handle_no_variable(state, str, result);
		return ;
	}
	var_len = get_var_name_length(str, state->i);
	if (var_len > 0)
		extract_expand_v(state, str, result, var_len);
	else
		handle_no_variable(state, str, result);
}
