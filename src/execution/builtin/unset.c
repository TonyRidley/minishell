/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:05:23 by tridley           #+#    #+#             */
/*   Updated: 2025/05/30 15:15:37 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"
#include "libft.h"

int	remove_env_ptr(char *var_name, char ***env_ptr);

int	builtin_unset(t_cmd *command, char ***env_ptr)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	while (command->args[i])
	{
		if (!is_valid_identifier(command->args[i]))
		{
			printf("unset: '%s':not a valid identifier\n", command->args[i]);
			exit_status = 1;
		}
		else
		{
			remove_env_ptr(command->args[i], env_ptr);
		}
		i++;
	}
	return (exit_status);
}

int	remove_env_ptr(char *var_name, char ***env_ptr)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(var_name);
	while ((*env_ptr)[i])
	{
		if (ft_strncmp((*env_ptr)[i], var_name, var_len) == 0 &&
		((*env_ptr)[i][var_len] == '=' || (*env_ptr)[i][var_len] == '\0'))
		{
			free((*env_ptr)[i]);
			while ((*env_ptr)[i + 1])
			{
				(*env_ptr)[i] = (*env_ptr)[i + 1];
				i++;
			}
			(*env_ptr)[i] = NULL;
			return (0);
		}
		i++;
	}
	return (0);
}
