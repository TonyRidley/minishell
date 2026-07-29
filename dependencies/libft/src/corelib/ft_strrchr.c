/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:04:58 by tridley           #+#    #+#             */
/*   Updated: 2024/10/08 17:04:59 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = -1;
	c = (unsigned char) c;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			tmp = i;
		i++;
	}
	if (s[i] == c)
		tmp = i;
	if (tmp >= 0)
		return ((char *)&s[tmp]);
	return (NULL);
}
