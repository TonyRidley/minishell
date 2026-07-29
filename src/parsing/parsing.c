/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:31:08 by tridley           #+#    #+#             */
/*   Updated: 2025/05/16 15:31:10 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "parsing.h"
#include "libft.h"

void	parse_token(t_token *token, char **env, t_cmd *command)
{
	t_cmd	*cmd_ptr;
	int		result;

	ft_memset(command, 0, sizeof(t_cmd));
	result = token_to_cmd(token, command, env);
	if (result != 0)
		return ;
	cmd_ptr = command;
	while (cmd_ptr)
	{
		result = expand_vars_from_cmd(cmd_ptr, env);
		if (result != 0)
			return ;
		cmd_ptr = cmd_ptr->next;
	}
}
