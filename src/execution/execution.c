/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:26:32 by mschuurm          #+#    #+#             */
/*   Updated: 2025/08/06 14:31:45 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"
#include "libft.h"

static int	exec_commands(t_cmd *command, char ***env_ptr);
static int	has_input_r(t_cmd *command);

static int	p_e_c(t_cmd *command, char ***env_ptr, int *o_stdin, int *o_stdout)
{
	if (!command || !env_ptr || !*env_ptr)
		return (0);
	if (command->heredoc_count > 0 && !command->previous && !command->next)
	{
		if (setup_heredoc(command, *env_ptr) != 0)
			return (g_exit_status);
	}
	if ((!command->args || !command->args[0]) && has_input_r(command))
	{
		if (setup_redirections(command, o_stdin, o_stdout, *env_ptr) != 0)
			return (g_exit_status = 1, g_exit_status);
		restore_redirections(*o_stdin, *o_stdout);
		return (0);
	}
	else if (!command->args || !command->args[0])
		return (0);
	shift_until_non_empty(command);
	if (!command->args[0])
		return (0);
	return (1);
}

int	execute_command(t_cmd *command, char ***env_ptr)
{
	int	o_stdin;
	int	o_stdout;
	int	result;

	o_stdin = -1;
	o_stdout = -1;
	if (p_e_c(command, env_ptr, &o_stdin, &o_stdout) != 1)
		return (g_exit_status);
	if (setup_redirections(command, &o_stdin, &o_stdout, *env_ptr) != 0)
		return (g_exit_status = 1, g_exit_status);
	result = exec_commands(command, env_ptr);
	restore_redirections(o_stdin, o_stdout);
	return (result);
}

static int	has_input_r(t_cmd *command)
{
	return (command->heredoc_count > 0 || command->redirect_in);
}

static int	exec_commands(t_cmd *command, char ***env_ptr)
{
	int		result;
	char	**env;

	env = *env_ptr;
	if (ft_strcmp(command->args[0], "cd") == 0)
		result = builtin_cd(command, env_ptr);
	else if (ft_strcmp(command->args[0], "echo") == 0)
		result = builtin_echo(command);
	else if (ft_strcmp(command->args[0], "env") == 0)
		result = builtin_env(env, command->args);
	else if (ft_strcmp(command->args[0], "exit") == 0)
		result = builtin_exit(command);
	else if (ft_strcmp(command->args[0], "export") == 0)
		result = builtin_export(command, env_ptr);
	else if (ft_strcmp(command->args[0], "pwd") == 0)
		result = builtin_pwd();
	else if (ft_strcmp(command->args[0], "unset") == 0)
		result = builtin_unset(command, &env);
	else
		result = execute_external_command(command, env);
	return (g_exit_status = result, result);
}
