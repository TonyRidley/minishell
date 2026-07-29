/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:40:56 by tridley           #+#    #+#             */
/*   Updated: 2025/06/10 19:11:47 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "parsing.h"
#include "execution.h"

static char	*find_command_path(const char *cmd, char **env);
static int	fork_and_execute(char *path, t_cmd *command, char **env);
static int	handle_parent_process(pid_t pid, char *path);

int	handle_path_errors(char *path, char *cmd_name)
{
	if (!path)
	{
		ft_putstr_fd(cmd_name, 2);
		return (write(2, ": command not found\n", 20),
			g_exit_status = 127, 127);
	}
	if (is_directory(path))
	{
		ft_putstr_fd(cmd_name, 2);
		return (write(2, " Is a directory\n", 16), g_exit_status = 126, 126);
	}
	if (!(access(path, X_OK) == 0))
	{
		ft_putstr_fd(cmd_name, 2);
		return (write(2, " Permission denied\n", 19), g_exit_status = 126, 126);
	}
	return (0);
}

int	execute_external_command(t_cmd *command, char **env)
{
	char	*path;
	int		result;
	int		error_code;

	if (!command->args[0] || command->args[0][0] == '\0')
		return (g_exit_status = 0, 0);
	if (((command->args[0][0] == '/') || (command->args[0][0] == '.'
		&& command->args[0][1] == '/')) && !file_exists(command->args[0]))
	{
		ft_putstr_fd(command->args[0], 2);
		return (ft_putstr_fd(": No such file or directory\n", 2),
			g_exit_status = 127, 127);
	}
	path = find_command_path(command->args[0], env);
	error_code = handle_path_errors(path, command->args[0]);
	if (error_code != 0)
		return (error_code);
	result = fork_and_execute(path, command, env);
	return (result);
}

static int	handle_parent_process(pid_t pid, char *path)
{
	int	status;

	free(path);
	disable_signal_handling();
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(STDOUT_FILENO, "^C\n", 3);
			g_exit_status = 130;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			write(STDOUT_FILENO, "^\\Quit (core dumped)\n", 21);
			g_exit_status = 131;
		}
		else
			g_exit_status = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	return (g_exit_status);
}

static int	fork_and_execute(char *path, t_cmd *command, char **env)
{
	pid_t	pid;
	int		result;

	pid = fork();
	if (pid == -1)
	{
		free(path);
		return (g_exit_status = 1, 1);
	}
	if (pid == 0)
	{
		setup_child_signals();
		execve(path, command->args, env);
		perror("execve");
		exit(127);
	}
	result = handle_parent_process(pid, path);
	return (result);
}

static char	*find_command_path(const char *cmd, char **env)
{
	char	**paths;
	char	*path_env;
	char	*result;

	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	path_env = NULL;
	while (env && *env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			path_env = *env + 5;
			break ;
		}
		env++;
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = try_command_paths(paths, cmd);
	return (result);
}
