/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:30:07 by tridley           #+#    #+#             */
/*   Updated: 2024/12/28 15:01:36 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	process_format(const char **p, va_list args)
{
	char	specifier;
	int		result;

	specifier = **p;
	result = specifier_handler(specifier, args);
	if (result == -1)
	{
		return (-1);
	}
	return (result);
}

static int	ft_printf_loop(const char *p, va_list args, int printed_chars)
{
	int	result;

	while (*p != '\0')
	{
		if (*p == '%' && *(p + 1) != '\0')
		{
			p++;
			result = process_format(&p, args);
			if (result == -1)
				return (-1);
			printed_chars += result;
		}
		else
		{
			result = write(1, p, 1);
			if (result == -1)
				return (-1);
			printed_chars++;
		}
		p++;
	}
	return (printed_chars);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	const char	*p;
	int			printed_chars;

	printed_chars = 0;
	p = format;
	va_start(args, format);
	printed_chars = ft_printf_loop(p, args, printed_chars);
	va_end(args);
	return (printed_chars);
}
