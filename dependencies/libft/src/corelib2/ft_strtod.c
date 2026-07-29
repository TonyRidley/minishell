/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:05:47 by tridley           #+#    #+#             */
/*   Updated: 2025/01/22 15:05:54 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

static double	parse_part(const char **str, double divisor, int is_fraction)
{
	double	result;

	result = 0.0;
	while (**str >= '0' && **str <= '9')
	{
		if (is_fraction)
		{
			result += (**str - '0') / divisor;
			divisor *= 10.0;
		}
		else
			result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	return (result);
}

double	ft_strtod(const char *str)
{
	double	result;
	double	fraction;
	int		is_negative;

	result = 0.0;
	fraction = 0.0;
	is_negative = 0;
	if (*str == '-')
	{
		is_negative = 1;
		str++;
	}
	else if (*str == '+')
		str++;
	result = parse_part(&str, 0.0, 0);
	if (*str == '.')
	{
		str++;
		fraction = parse_part(&str, 10.0, 1);
	}
	result += fraction;
	if (is_negative)
		result = -result;
	return (result);
}
