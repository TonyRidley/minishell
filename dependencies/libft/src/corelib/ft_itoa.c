/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:42:03 by tridley           #+#    #+#             */
/*   Updated: 2024/10/09 14:42:05 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int number)
{
	int	digits;

	digits = 0;
	if (number == 0)
		return (1);
	if (number < 0)
		number = -number;
	while (number > 0)
	{
		number /= 10;
		digits++;
	}
	return (digits);
}

static char	*allocate_memory(int digits, int is_negative)
{
	char	*str;

	str = (char *)malloc((digits + is_negative + 1) * sizeof(char));
	if (!str)
		return (NULL);
	return (str);
}

void	reverse_string(char *str, int length)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = length - 1;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

char	*ft_itoa(int n)
{
	int		is_negative;
	int		i;
	char	*str;

	is_negative = n < 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = allocate_memory(count_digits(n), is_negative);
	if (!str)
		return (NULL);
	i = 0;
	if (is_negative)
		n = -n;
	while (n > 0)
	{
		str[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (is_negative)
		str[i++] = '-';
	str[i] = '\0';
	reverse_string(str, i);
	return (str);
}
