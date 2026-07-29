/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:54:18 by tridley           #+#    #+#             */
/*   Updated: 2025/07/09 15:19:52 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "parsing.h"
#include "minishell.h"
#include "execution.h"
#include "libft.h"

volatile int	g_exit_status = 0;

int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	char	**env;

	(void)argc;
	(void)argv;
	setup_signals();
	env = copy_envp(envp);
	while (1)
	{
		setup_signals();
		line = readline("\001\033[34m\002Minishell>$ \001\033[0m\002");
		if (!line)
		{
			ft_printf("exit\n");
			break ;
		}
		add_history(line);
		lex_parse_execute(line, &env);
		free(line);
	}
	free_env(env);
	return (0);
}

static void	handle_execution(t_cmd *command, char ***env_ptr)
{
	int	tty;

	if (!command->next)
		execute_command(command, env_ptr);
	else
		execute_pipeline(command, env_ptr);
	free_cmd(command);
	if (!isatty(STDIN_FILENO))
	{
		tty = open("/dev/tty", O_RDONLY);
		if (tty != -1)
		{
			dup2(tty, STDIN_FILENO);
			close(tty);
		}
	}
}

int	lex_parse_execute(char *line, char ***env_ptr)
{
	t_token	*token;
	t_cmd	*command;

	token = tokenize_input(line);
	if (token == NULL)
		return (1);
	command = ft_calloc(1, sizeof(t_cmd));
	if (!command)
		return (1);
	parse_token(token, *env_ptr, command);
	free_tokens(token);
	handle_execution(command, env_ptr);
	return (g_exit_status);
}

char	**copy_envp(char **envp)
{
	char	**envp_copy;
	int		envp_count;
	int		i;

	envp_count = 0;
	while (envp[envp_count])
		envp_count++;
	envp_copy = malloc(sizeof(char *) * (envp_count + 1));
	if (!envp_copy)
		return (NULL);
	i = 0;
	while (i < envp_count)
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (!envp_copy[i])
		{
			while (--i >= 0)
				free(envp_copy[i]);
			free(envp_copy);
			return (NULL);
		}
		i++;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}

void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
