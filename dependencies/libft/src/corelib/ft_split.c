/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:41:52 by tridley           #+#    #+#             */
/*   Updated: 2024/10/09 14:41:53 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_substrings(char const *s, char c)
{
	size_t	i;
	size_t	delimiter_count;
	size_t	in_str;

	i = 0;
	delimiter_count = 0;
	in_str = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c && in_str == 0)
		{
			in_str = 1;
			delimiter_count++;
		}
		else if (s[i] == c)
			in_str = 0;
		i++;
	}
	return (delimiter_count);
}

static void	free_strings(char **strings, size_t substr_count)
{
	while (substr_count)
		free(strings[--substr_count]);
	free(strings);
}

static char	**allocate_strings(size_t substr_count)
{
	char	**strings;
	size_t	i;

	i = 0;
	strings = malloc((substr_count + 1) * sizeof(char *));
	if (!strings)
		return (NULL);
	while (i <= substr_count)
	{
		strings[i] = NULL;
		i++;
	}
	return (strings);
}

static int	fill_strings(char **strings, char const *s, char c)
{
	size_t	start;
	size_t	str_index;
	size_t	end;

	start = 0;
	str_index = 0;
	end = 0;
	while (s[start])
	{
		if (s[start] != c)
		{
			end = start;
			while (s[end] && s[end] != c)
				end++;
			strings[str_index] = ft_substr(s, start, end - start);
			if (!strings[str_index])
				return (0);
			str_index++;
			start = end;
		}
		else
			start++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;
	size_t	substr_count;

	if (!s)
		return (NULL);
	substr_count = count_substrings(s, c);
	strings = allocate_strings(substr_count);
	if (!strings)
		return (NULL);
	if (substr_count == 0)
		return (strings);
	if (!fill_strings(strings, s, c))
	{
		free_strings(strings, substr_count);
		return (NULL);
	}
	return (strings);
}
