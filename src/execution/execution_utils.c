/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:07:23 by tridley           #+#    #+#             */
/*   Updated: 2025/05/22 18:07:26 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"
#include "libft.h"

void	shift_until_non_empty(t_cmd *command)
{
	int	i;

	if (!command || !command->args)
		return ;
	while (command->args[0] && command->args[0][0] == '\0')
	{
		i = 0;
		while (command->args[i + 1])
		{
			command->args[i] = command->args[i + 1];
			i++;
		}
		command->args[i] = NULL;
		if (i == 0)
			break ;
	}
}

int	check_pwd_exists(char ***env_ptr)
{
	int	i;
	int	pwd_exists;

	i = 0;
	pwd_exists = 0;
	while ((*env_ptr)[i])
	{
		if (ft_strncmp((*env_ptr)[i], "PWD=", 4) == 0)
		{
			pwd_exists = 1;
			break ;
		}
		i++;
	}
	return (pwd_exists);
}
