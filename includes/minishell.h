/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:49:35 by tridley           #+#    #+#             */
/*   Updated: 2025/07/08 17:59:18 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "error_ids.h"
# include <fcntl.h>

extern volatile int	g_exit_status;

int		lex_parse_execute(char *line, char ***env_ptr);
void	setup_signals(void);
char	**copy_envp(char **envp);
void	free_env(char **env);
void	disable_signal_handling(void);
void	setup_child_signals(void);
int		was_sigint_received(void);
void	setup_heredoc_signals(void);
int		was_heredoc_interrupted(void);

void	disable_signal_handling(void);
void	setup_child_signals(void);

#endif
