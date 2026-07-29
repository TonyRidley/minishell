/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:05:31 by tridley           #+#    #+#             */
/*   Updated: 2025/06/03 15:17:23 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_printf.h"

int	builtin_env(char **env, char **args)
{
	int	i;

	if (!env)
		return (1);
	if (args[1])
	{
		printf("env: '%s': No such file or directory\n", args[1]);
		return (127);
	}
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			ft_printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
