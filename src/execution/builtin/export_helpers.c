/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:19:57 by tridley           #+#    #+#             */
/*   Updated: 2025/05/26 14:20:02 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"
#include "libft.h"

static int	get_sort_len(char **array, int j);

void	print_export_format(char *env_string)
{
	char	*eq_pos;
	int		key_len;

	eq_pos = ft_strchr(env_string, '=');
	if (!eq_pos)
	{
		printf("declare -x %s\n", env_string);
		return ;
	}
	key_len = eq_pos - env_string;
	printf("declare -x %.*s=\"%s\"\n", key_len, env_string, eq_pos + 1);
}

char	**sortand_copy_env(char ***env_ptr)
{
	int		i;
	int		count;
	char	**sort_copy_env;

	count = 0;
	while ((*env_ptr)[count] != NULL)
		count++;
	sort_copy_env = malloc(sizeof(char *) * (count + 1));
	if (!sort_copy_env)
		return (NULL);
	sort_copy_env[count] = NULL;
	i = 0;
	while (i < count)
	{
		sort_copy_env[i] = ft_strdup((*env_ptr)[i]);
		i++;
	}
	bubble_sort(sort_copy_env, count);
	return (sort_copy_env);
}

void	bubble_sort(char **array, int count)
{
	int		i;
	int		j;
	char	*temp;
	int		len;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			len = get_sort_len(array, j);
			if (ft_strncmp(array[j], array[j + 1], len) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static int	get_sort_len(char **array, int j)
{
	int		len1;
	int		len2;
	char	*eq_pos1;
	char	*eq_pos2;

	eq_pos1 = ft_strchr(array[j], '=');
	eq_pos2 = ft_strchr(array[j + 1], '=');
	if (eq_pos1)
		len1 = eq_pos1 - array[j];
	else
		len1 = ft_strlen(array[j]);
	if (eq_pos2)
		len2 = eq_pos2 - array[j + 1];
	else
		len2 = ft_strlen(array[j + 1]);
	if (len1 < len2)
		return (len1);
	return (len2);
}

void	free_string_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
