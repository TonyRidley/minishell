/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:04:59 by tridley           #+#    #+#             */
/*   Updated: 2025/07/08 18:06:17 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "parsing.h"
#include "libft.h"
#include "execution.h"

static char	*get_target_path(t_cmd *command, char **env_ptr)
{
	char	*path;

	if (command->args[2] != NULL)
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		g_exit_status = 1;
		return (NULL);
	}
	if (command->args[1] != NULL)
		path = command->args[1];
	else
	{
		path = get_env_value("HOME", env_ptr);
		if (path == NULL || *path == '\0')
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			g_exit_status = 1;
			return (NULL);
		}
	}
	return (path);
}

static int	validate_path(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		ft_putstr_fd("cd: No such file or directory\n", 2);
		g_exit_status = 1;
		return (0);
	}
	if (!S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("cd: Not a directory\n", 2);
		g_exit_status = 1;
		return (0);
	}
	return (1);
}

static void	update_oldpwd(int pwd_exists, char ***env_ptr)
{
	char	*old_pwd;
	char	*oldpwd_var;

	if (pwd_exists)
	{
		old_pwd = get_env_value("PWD", *env_ptr);
		if (old_pwd && *old_pwd)
		{
			oldpwd_var = ft_strjoin("OLDPWD=", old_pwd);
			if (oldpwd_var)
			{
				add_to_env(oldpwd_var, env_ptr, 0);
				free(oldpwd_var);
			}
		}
	}
	else
		remove_env_ptr("OLDPWD", env_ptr);
}

static int	update_pwd(char ***env_ptr)
{
	char	cwd_buffer[PATH_MAX];
	char	*new_pwd;

	if (getcwd(cwd_buffer, PATH_MAX) == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory\n", 2);
		g_exit_status = 1;
		return (0);
	}
	new_pwd = ft_strjoin("PWD=", cwd_buffer);
	if (new_pwd)
	{
		add_to_env(new_pwd, env_ptr, 0);
		free(new_pwd);
	}
	return (1);
}

int	builtin_cd(t_cmd *command, char ***env_ptr)
{
	char	*path;
	int		pwd_exists;

	pwd_exists = check_pwd_exists(env_ptr);
	path = get_target_path(command, *env_ptr);
	if (!path)
		return (1);
	if (!validate_path(path))
		return (1);
	update_oldpwd(pwd_exists, env_ptr);
	if (chdir(path) == -1)
		return (perror("cd"), g_exit_status = 1, 1);
	if (!update_pwd(env_ptr))
		return (1);
	return (0);
}
