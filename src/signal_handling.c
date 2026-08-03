/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:01:48 by mschuurm          #+#    #+#             */
/*   Updated: 2025/07/09 14:44:13 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <termios.h>
#include "minishell.h"

static void	simple_sigint_handler(int sig)
{
	(void) sig;
	write(1, "^C\n", 3);
	close(0);
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, simple_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 130;
}

void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct termios		term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}
