/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:15:40 by tridley           #+#    #+#             */
/*   Updated: 2024/10/16 16:15:42 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*create_new_element(void *content, void (*del)(void *))
{
	t_list	*new_element;

	new_element = ft_lstnew(content);
	if (new_element == NULL)
	{
		del(content);
	}
	return (new_element);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_element;
	void	*new_content;

	new_list = NULL;
	if (lst == NULL || f == NULL)
		return (NULL);
	while (lst)
	{
		new_content = f(lst->content);
		new_element = create_new_element(new_content, del);
		if (!new_element)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_element);
		lst = lst->next;
	}
	return (new_list);
}
