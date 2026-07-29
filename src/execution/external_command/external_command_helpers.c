/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:31:23 by tridley           #+#    #+#             */
/*   Updated: 2025/06/10 19:53:28 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "parsing.h"
#include "execution.h"

static void	free_path_array(char **paths);
static char	*create_full_path(char **paths, const char *cmd, int i);

char	*try_command_paths(char **paths, const char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = create_full_path(paths, cmd, i);
		if (!full_path)
		{
			free_path_array(paths);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_path_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_path_array(paths);
	return (NULL);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

int	file_exists(const char *path)
{
	struct stat	path_stat;

	return (stat(path, &path_stat) == 0);
}

static char	*create_full_path(char **paths, const char *cmd, int i)
{
	char	*full_path;

	full_path = malloc(ft_strlen(paths[i]) + ft_strlen(cmd) + 2);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, paths[i], ft_strlen(paths[i]) + 1);
	ft_strlcat(full_path, "/", ft_strlen(paths[i]) + 2);
	ft_strlcat(full_path, cmd, ft_strlen(paths[i]) + ft_strlen(cmd) + 2);
	return (full_path);
}

static void	free_path_array(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}
