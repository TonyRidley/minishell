/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:04:48 by tridley           #+#    #+#             */
/*   Updated: 2025/06/03 14:24:07 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"
#include "libft.h"

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(t_cmd *command)
{
	char	**args;
	int		i;
	int		no_nl;

	if (!command || !command->args)
		return (1);
	args = command->args;
	i = 1;
	no_nl = 0;
	while (args[i] && is_n_flag(args[i]))
	{
		no_nl = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (no_nl == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
