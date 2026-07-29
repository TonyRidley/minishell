/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:05:16 by tridley           #+#    #+#             */
/*   Updated: 2025/06/10 16:16:42 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"
#include "libft.h"

int	display_sorted_env(char ***env_ptr);

int	builtin_export(t_cmd *command, char ***env_ptr)
{
	int	status;
	int	i;
	int	equals_pos;

	equals_pos = 0;
	status = 0;
	if (command->args[1] == NULL)
		return (display_sorted_env(env_ptr));
	i = 1;
	while (command->args[i])
	{
		if (!is_valid_identifier(command->args[i]))
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(command->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
			add_to_env(command->args[i], env_ptr, equals_pos);
		i++;
	}
	g_exit_status = status;
	return (status);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || str[0] == '\0' || str[0] == '=' || ft_isdigit(str[0]))
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	add_to_env(char *var, char ***env_ptr, int equals_pos)
{
	char	*var_name;
	int		i;

	while (var[equals_pos] && var[equals_pos] != '=')
		equals_pos++;
	var_name = ft_substr(var, 0, equals_pos);
	if (!var_name)
		return (1);
	i = 0;
	while ((*env_ptr)[i])
	{
		if (ft_strncmp((*env_ptr)[i], var_name, equals_pos) == 0 &&
			((*env_ptr)[i][equals_pos] == '=' ||
				(*env_ptr)[i][equals_pos] == '\0'))
		{
			if (var[equals_pos] == '=')
			{
				free((*env_ptr)[i]);
				(*env_ptr)[i] = ft_strdup(var);
			}
			return (free(var_name), 0);
		}
		i++;
	}
	return (free(var_name), add_new_var(var, env_ptr));
}

int	add_new_var(char *var, char ***env_ptr)
{
	char	**new_env;
	int		env_size;
	int		i;

	env_size = 0;
	while ((*env_ptr)[env_size])
		env_size++;
	new_env = malloc(sizeof(char *) * (env_size + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (i < env_size)
	{
		new_env[i] = (*env_ptr)[i];
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	free(*env_ptr);
	*env_ptr = new_env;
	return (0);
}

int	display_sorted_env(char ***env_ptr)
{
	char	**sorted_env;
	int		i;

	sorted_env = sortand_copy_env(env_ptr);
	if (!sorted_env)
		return (1);
	i = 0;
	while ((*env_ptr)[i] != NULL)
	{
		print_export_format(sorted_env[i]);
		i++;
	}
	free_string_array(sorted_env);
	return (0);
}
