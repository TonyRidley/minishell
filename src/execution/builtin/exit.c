/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:05:37 by tridley           #+#    #+#             */
/*   Updated: 2025/05/26 13:50:37 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"
#include "libft.h"

static int	is_valid_numeric(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	builtin_exit(t_cmd *command)
{
	long	exit_code;

	ft_putstr_fd("exit\n", 1);
	if (!command->args[1])
	{
		rl_clear_history();
		exit(g_exit_status);
	}
	if (!is_valid_numeric(command->args[1]))
	{
		ft_putstr_fd("numeric argument required\n", 2);
		rl_clear_history();
		exit(2);
	}
	exit_code = ft_atol(command->args[1]);
	if (command->args[2])
	{
		ft_putstr_fd("too many arguments\n", 2);
		g_exit_status = 1;
		return (1);
	}
	rl_clear_history();
	exit((unsigned char)exit_code);
}
