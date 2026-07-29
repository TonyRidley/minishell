/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:15:31 by tridley           #+#    #+#             */
/*   Updated: 2024/10/16 16:15:50 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;
	t_list	*next_node;

	if (f == NULL || lst == NULL)
		return ;
	current = lst;
	while (current != NULL)
	{
		next_node = current->next;
		f(current->content);
		current = next_node;
	}
}
