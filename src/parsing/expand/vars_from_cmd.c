/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_from_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:48:44 by tridley           #+#    #+#             */
/*   Updated: 2025/06/10 20:08:52 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "minishell.h"
#include "parsing.h"

static bool	expand_redirections(char **envp, char **expanded, char **redirect);

int	expand_vars_from_cmd(t_cmd *command, char **env)
{
	int		i;
	char	*expanded;

	i = 0;
	while (command->args[i])
	{
		expanded = expand_env_vars(command->args[i], env);
		if (!expanded)
			return (ERR_EXPANSION);
		command->args[i] = expanded;
		i++;
	}
	if (command->redirect_in)
		if (!expand_redirections(env, &expanded, &command->redirect_in))
			return (ERR_EXPANSION);
	if (command->redirect_out)
		if (!expand_redirections(env, &expanded, &command->redirect_out))
			return (ERR_EXPANSION);
	if (command->append)
		if (!expand_redirections(env, &expanded, &command->append))
			return (ERR_EXPANSION);
	return (0);
}

static bool	expand_redirections(char **env, char **expanded, char **redirect)
{
	char	*old_redirect;

	old_redirect = *redirect;
	*expanded = expand_env_vars(*redirect, env);
	if (!(*expanded))
		return (false);
	free(old_redirect);
	*redirect = *expanded;
	return (true);
}
