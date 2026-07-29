/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:41:31 by tridley           #+#    #+#             */
/*   Updated: 2024/10/09 14:41:32 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_len;

	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	total_len = s1_len + s2_len;
	if (!s1 || !s2)
		return (NULL);
	str = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = s1_len;
	while (i--)
		str[i] = s1[i];
	i = 0;
	while (s2_len--)
	{
		str[s1_len + i] = s2[i];
		i++;
	}
	str[total_len] = '\0';
	return (str);
}
